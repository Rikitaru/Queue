#include <iostream>
#include <cstdlib>
using namespace std;
struct Point {
    int x;
    int y;
    int z;
    Point() {
        this->x = 1;
        this->y = 2;
        this->z = 3;
    }
    Point& operator= (const Point& point) //перегрузка оператора присваивания, создание нового объекта структуры
    {
        this->x = point.x;
        this->y = point.y;
        this->z = point.z;
        return *this;
    }

    Point& operator= (const int a) //перегрузка оператора присваивания, создание нового объекта структуры (обнуление)
    {
        this->x = a;
        this->y = a;
        this->z = a;
        return *this;
   }
   friend std::ostream& operator<< (std::ostream& out, const Point& point);
   friend std::istream& operator>> (std::istream& in, Point& point);
};

std::ostream& operator<< (std::ostream& out, const Point& point) {
    // Поскольку operator<< является другом класса Point, то мы имеем прямой доступ к членам Point
    out << "Point(" << point.x << ", " << point.y << ", " << point.z << ")";
    return out;
}
std::istream& operator>> (std::istream& in, Point& point)
{
    // Поскольку operator>> является другом класса Point, то мы имеем прямой доступ к членам Point.
    // Обратите внимание, параметр point (объект класса Point) должен быть неконстантным, чтобы мы имели возможность изменить члены класса
    in >> point.x;
    cout << "Введите Y = ";
    in >> point.y;
    cout << "Введите Z = ";
    in >> point.z;
    return in;
}

template <typename T>
struct el {//структура каждого элемента очереди состоит из
    el();
    T x; //значение элемента очереди
    el* previous; //указатель на предыдущий элемент очереди
};

template<typename T>
el<T>::el() {
    x = 0;
    previous = nullptr;
}

template <class T>
class Queue //класс очередь
{
private:
    int count; //размер очереди
    el <T>* head; //голова очереди
public:
    Queue() { head = nullptr; count = 0; }; //конструктор
    // Конструктор копирования
    Queue(const Queue& queue) { //конструктор копирования this - это очередь в которую нужно скопировать (новая), queue - очередь, из которой мы делаем копию (берем данные)
        this->head = new el <T>;//у новой очереди создаем пустую голову
        this->head->x = queue.head->x;//в новой голове копируем элемент Х(либо число, либо Pointer, для этого оператор присваивания перегрузили у Pointer)
        this->count = queue.count;//копируем количество элементов в очереди
        el <T>* current_this = this->head; //указатель новой очереди на голову
        el <T>* current_queue = queue.head;//указатель старой queue очереди на голову
        //здесь мы уже скопировали голову очереди
        while (current_queue->previous != nullptr) //условие: пока указатель на элемент старой очереди не указывает в пустоту (не последний)
            {
            current_this->previous = new el <T>; //создаем новый элемент по указателю на следующий элемент в новой очереди, далее перейдем на этот элемент
            current_this = current_this->previous; //переход указателя на элемент новой очереди на "следующий" элемент oчереди (переходим на элемент ближе к первому), далее перейдем на старой очереди на следующий элемент
            current_queue = current_queue->previous; //переход указателя на элемент старой очереди на "следующий" элемент oчереди (переходим на элемент ближе к первому)
            current_this->x = current_queue->x; //в новом элементе новой очереди копируем элемент Х(либо число, либо Pointer, для этого оператор присваивания перегрузили у Pointer)
            }
        //здесь мы дошли до последнего элемента очереди скопировали уже все элементы старой очереди в новую, но последний  указатель не обнулили
        current_this->previous = nullptr;
        //очередь скоирована. голова есть и ее не меняли, потом прошли указателями двумя по обеим очередям, создавали новые элементы через new и туда копировали значения!
        cout << "Copy constructor worked here!\n";
    }
    int size(); //метод -> возвращает count
    void show(); //метод вывода очереди
    void enqueue(); //добавление нового элемента в очередь
    void cut();//метод удаления элемента из очереди
    void clear();//метод удаления всей очереди
    void deque();
};

template <class T>
int Queue <T>::size() { //функция получения размера очереди
    return count;//возвращаем значение счетчика количества элементов в очереди
}
template <class T>
void Queue<T>::enqueue() {//функция вставки нового элемента
    if (!count) {//Так как очередь пуста, то создаем головной элемент
        head = new el <T>;//создаем по указателю новый элемент
        head->previous = nullptr;//пускай он указывает в пустоту
        cout << "Х = ";//ввод значения нового элемента (головы)
        cin >> head->x;//сохранение результата
        count++;//увеличение счетчика длины очереди
        cout << "Элемент успешно добавлен" << endl;
        system("pause");
    }
    else
    {//если голова есть в очереди -> добавляем новый элемент
        auto* current = new el <T>;//el <T> *current = new el <T>;//создаем по указателю новый элемент
        cout << "x = ";//ввод значения нового элемента
        cin >> current->x;//сохранение результата
        current->previous = head;//пускай новый элемент указывает на головной элемент
        head = current;//пускай голова теперь указывает на новый элемент
        count++;//увеличение счетчика длины очереди
        cout << "Элемент успешно добавлен" << endl;
        system("pause");
            }
        }
        template <class T>
void Queue<T>::cut() {//удаление элемента в очереди
    //если голова пустая, то ничего делать не нужно
    if (!count) {//Так как очередь пуста, ничего не делаем
        cout << "Очередь пуста" << endl;
        system("pause");
        return;
    }
    el <T>* current = head; //указатель на голову
    el <T>* buf = head; //временный указатель на голову (для удаления)

    if (count > 1) {//Так как очередь пуста, ничего не делаем
        //удаляем элемент очереди
        while (current->previous->previous != nullptr) //условие: пока не найдем второй элемент с начала очереди (второй пришедший)
            {
            current = current->previous; //переход на предыдущий элемент oчереди (переходим на элемент ближе к первому)
            }
        buf = current->previous; //переход на первый элемент очереди, который будем удалять
        current->previous = nullptr;//обнуление связи со второго элемента очереди на первый
    }
    count--;//уменьшение длины очереди
    delete(buf);//удаление первого элемента
    cout << "Элемент успешно извлечен из очереди" << endl;
    system("pause");
}
template <class T>
void Queue<T>::clear() {//удаление элемента в очереди
    //если голова пустая, то ничего делать не нужно
    if (!count) {//Так как очередь пуста, ничего не делаем
        cout << "Очередь пуста" << endl;
        system("pause");
        return;
    }

    while (count > 1) {
        el <T>* current = head; //указатель на голову
        el <T>* buf = head; //временный указатель на голову (для удаления)
        //удаляем элемент очереди
        while (current->previous->previous != nullptr) //условие: пока не найдем второй элемент с начала очереди (второй пришедший)
            {
            current = current->previous; //переход на предыдущий элемент oчереди (переходим на элемент ближе к первому)
            }
        buf = current->previous; //переход на первый элемент очереди, который будем удалять
        current->previous = nullptr;//обнуление связи со второго элемента очреди на первый
        count--;//уменьшение длины очереди
        delete(buf);
        cout << "Элемент успешно извлечен из очереди" << endl;
    }

    el <T>* buf = head; //временный указатель на голову (для удаления)
    count--;//уменьшение длины очереди
    delete(buf);

    system("pause");
}
template <class T>
void Queue<T>::show() {
    int i = size(); //получаем значение длины очереди
    el <T>* current = head;//указаетль на голову
    if (!count)//Так как очередь пуста, ничего не делаем
        {
        cout << "Очередь пуста" << endl;
        system("pause");
        return;
        }
    cout << "Старший элемент по очереди - головной элемент (последний пришедший)." << endl;
    //если есть очередь, то выводим циклично, пока не закончится очередь
    cout << "[" << --i << "] " << current->x << endl;//вывод значение элемента очереди
    while (current->previous != nullptr) {//цикл прохода от головы до первопрешедшего элемента
        current = current->previous;//переход на предыдущий элемент oчереди (переходим на элемент ближе к первому)
        cout << "[" << --i << "] " << current->x << endl;//вывод значение элемента очереди
    }
    system("pause");
}
template<class T>
void Queue<T>::deque() {
    if (count < 1) {
        cout << "Очередь пуста, будет выкинуто исключение" << endl;
        throw "Ошибка. Очередь пуста.";
    }
}

int main()
{
    //system("chcp 65001");
    setlocale(LC_ALL, "Russian");
    Queue<Point> a;
    Queue <int> b;

    int answer;
    cout << "Выберите тип очереди: 0-int, 1-Point" << endl;
    cin >> answer;
    int menu;
    try {
        while (true) {
            system("CLS");
            cout << "1 – Добавление элемента в конец очереди" << endl
            << "2 – Извлечение с начала очереди" << endl
            << "3 – Вывод очереди на экран" << endl
            << "4 – Удаление всей очереди" << endl
            << "5 – Проверка на пустоту с выбрасывание исключения!" << endl
            << "6 – Конструктор копирования шаблонной очереди" << endl
            << "7 – Выход из программы" << endl;
            cin >> menu;
            switch (menu)
            {
                case 7: {
                    return 0;
                }
                case 1: { //переход в функцию вставки
                    (answer == 1) ? a.enqueue() : b.enqueue();//вызов метода вставки
                    break;
                }
                case 2: { //переход в функцию вырезки
                    (answer == 1) ? a.cut() : b.cut();//вызов метода удаления
                    break;
                }
                case 3: {  //переход в функцию вывода на экран очереди
                    (answer == 1) ? a.show() : b.show();//вызов метода вывода
                    break;
                }
                case 4: {  //переход в функцию очистки всей очереди
                    (answer == 1) ? a.clear() : b.clear();//вызов метода вывода
                    break;
                }
                case 5: {  //переход в функцию очистки всей очереди
                    (answer == 1) ? a.deque() : b.deque();//вызов метода вывода
                    break;
                }
                case 6: {  //переход в функцию очистки всей очереди
                    if (answer == 1) {
                        Queue<Point> c = a; //сработает конструктор копирования, так как у нас инициализация
                        cout << "новая очередь через Конструктор копирования"<< endl;
                        c.show();
                        cout << "a.clear();" << endl;
                        a.clear();
                        cout << "c.show();" << endl;
                        c.show();
                    }
                    else {
                        Queue<int> d = b; //сработает конструктор копирования, так как у нас инициализация
                        cout << "новая очередь через Конструктор копирования" << endl;
                        d.show();
                        cout << "b.clear();" << endl;
                        b.clear();
                        cout << "d.show();" << endl;
                        d.show();
                    }
                    break;
                }
                default:
                    break;
            }
        }
    }
    catch (char* a) {
        cout << "Мы поймали исключение. " << a << endl;
    }
}