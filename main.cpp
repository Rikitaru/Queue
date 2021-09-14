#include <iostream>
#include <cstdlib>
using namespace std;
struct Point{
    int x;
    int y;
    int z;
    Point(){
        this->x=1;
        this->y=2;
        this->z=3;
    }
    friend std::ostream& operator<< (std::ostream &out, const Point &point);
    friend std::istream& operator>> (std::istream &in, Point &point);
};

std::ostream& operator<< (std::ostream &out, const Point &point) {
    // Поскольку operator<< является другом класса Point, то мы имеем прямой доступ к членам Point
    out << "Point(" << point.x << ", " << point.y << ", " << point.z << ")";
    return out;
}
std::istream& operator>> (std::istream &in, Point &point)
{
    // Поскольку operator>> является другом класса Point, то мы имеем прямой доступ к членам Point.
    // Обратите внимание, параметр point (объект класса Point) должен быть неконстантным, чтобы мы имели возможность изменить члены класса
    in >> point.x;
    cout <<"Введите Y = ";
    in >> point.y;
    cout <<"Введите Z = ";
    in >> point.z;
    return in;
}

template <typename T>
struct el {//структура каждого элемента очереди состоит из
    el();
    T x; //значение элемента очереди
    el *previous; //указатель на предыдущий элемент очереди
};

template<typename T>
el<T>::el() {
    T t;
}

template <class T>
class Queue //класс очередь
{
private:
    int count; //размер очереди
    el <T> *head; //голова очереди
public:
    Queue(){ head = nullptr; count = 0;}; //конструктор
    int size(); //метод -> возвращает count
    void show(); //метод вывода очереди
    void enqueue(); //добавление нового элемента в очередь
    void cut();//метод удаления элемента из очереди
    void clear();//метод удаления всей очереди
    void deque() const;
};

template <class T>
int Queue <T>::size() { //функция получения размера очереди
    return count;//возвращаем значение счетчика количества элементов в очереди
}


template <class T>
void Queue<T>::enqueue() {//функция вставки нового элемента
    if(!count) {//Так как очередь пуста, то создаем головной элемент
        head =  new el <T>;//создаем по указателю новый элемент
        head->previous = nullptr;//пускай он указывает в пустоту
        cout << "Х = ";//ввод значения нового элемента (головы)
        cin >> head->x;//сохранение результата
        count++;//увеличение счетчика длины очереди
        cout << "Элемент успешно добавлен" << endl;
        system("pause");
    }
    else
    {//если голова есть в очереди -> добавляем новый элемент
        auto *current = new el <T>;//el <T> *current = new el <T>;//создаем по указателю новый элемент
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
    el <T> *current = head; //указатель на голову
    el <T> *buf = head; //временный указатель на голову (для удаления)

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
    el <T> *current = head; //указатель на голову
    el <T> *buf = head; //временный указатель на голову (для удаления)
    while (count > 0){
        //удаляем элемент очереди
        while (current->previous != nullptr) //условие: пока не найдем второй элемент с начала очереди (второй пришедший)
            {
            current = current->previous; //переход на предыдущий элемент oчереди (переходим на элемент ближе к первому)
            }
        buf = current->previous; //переход на первый элемент очереди, который будем удалять
        current->previous = nullptr;//обнуление связи со второго элемента очреди на первый
        count--;//уменьшение длины очереди
        delete(buf);//удаление первого элемента
        cout << "Элемент успешно извлечен из очереди" << endl;
    }
    system("pause");
}
template <class T>
void Queue<T>::show() {
    int i = size(); //получаем значение длины очереди
    el <T> *current = head;//указаетль на голову
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
void Queue<T>::deque() const{
    if (count < 1){
        cout << "Очередь пуста, будет выкинуто исключение" << endl;
        throw "Ошибка. Очередь пуста.";
    }
}

int main()
{
    system("chcp 65001");
    //setlocale(LC_ALL, "Russian");
    Queue <Point> a;
    Queue <int> b;
    int answer;
    cout <<"Выберите тип очереди: 0-int, 1-Point"<<endl;
    cin>>answer;
    int menu;
    try{
        while(true){
            system("CLS");
            cout << "1 – Добавление элемента в конец очереди" << endl
            << "2 – Извлечение с начала очереди" << endl
            << "3 – Вывод очереди на экран" << endl
            << "4 – Удаление всей очереди" << endl
            << "5 – Проверка на пустоту с выбрасывание исключения!" << endl
            << "7 – Выход из программы" << endl;
            cin >> menu;
            switch (menu)
            {
                case 7: {
                    return 0;
                }
                case 1: { //переход в функцию вставки
                    (answer==1) ? a.enqueue() : b.enqueue();//вызов метода вставки
                    break;
                }
                case 2: { //переход в функцию вырезки
                    (answer==1)?a.cut():b.cut();//вызов метода удаления
                    break;
                }
                case 3: {  //переход в функцию вывода на экран очереди
                    (answer==1)?a.show():b.show();//вызов метода вывода
                    break;
                }
                case 4: {  //переход в функцию очистки всей очереди
                    (answer==1)?a.clear():b.clear();//вызов метода вывода
                    break;
                }
                case 5: {  //переход в функцию очистки всей очереди
                    (answer==1)?a.deque():b.deque();//вызов метода вывода
                    break;
                }
                default:
                    break;
            }
        }
    }
    catch (char* a ){
        cout <<"Мы поймали исключение. "<<a<<endl;
    }
}