#include <iostream>
//реализация связанного списка позволяет динамически изменять размер буфера.
// Он может меняться в зависимости от количества элементов
//и если в реализации с массивом мы выделяем память сразу, так в этом это не так. и
//использование связного списка оберегает от выделения лишнего пространства
//доступ к элементам связанного списка требует перемещения по списку от начала
//до нужной позиции. Этот обход может быть медленнее по сравнению с прямым доступом к массиву.

class TheRing { //One ring to rule them all!
private:
    struct Node {
        int data;
        Node* next;
    };

    Node* head;
    Node* tail;
    int capacity;
    int size;

public:

    TheRing(int capacity) {
        this->capacity = capacity;
        size = 0;
        head = nullptr;
        tail = nullptr;
    }


    ~TheRing() {
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }


    bool isEmpty() {
        return size == 0;
    }


    bool isFull() {
        return size == capacity;
    }


    void enqueue(int item) {
    if (isFull()) {
        return;
    }
    Node* newNode = new Node;
    newNode->data = item;
    newNode->next = nullptr;
    if (isEmpty()) {
        head = newNode;
        tail = newNode;
    }
    else {
        tail->next = newNode;
        tail = newNode;
    }
    size++;
}


    void dequeue() {
        if (isEmpty()) {
            return;
        }
        Node* temp = head;
        head = head->next;
        delete temp;
        size--;
    }


    int getFront() {
        if (isEmpty()) {
            return -1;
        }
        return head->data;
    }
};



// в первом классе я использкю массив в качестве буфера. Это Эффективный подход т.к я пользователь сразу при создании
//класса может задать размер массива. И программе не потребуется динамически выделять память.
//также чем отличается массив от связного списка так это тем что можно быстро достать значение из массива.
//минусы же это то что
//реализация массива имеет фиксированную емкость, что означает, что она не может динамически изменять
//размер для размещения большего количества элементов, чем его
//первоначальная емкость. Если буфер заполняется, дальнейшие операции постановки в очередь перезапишут существующие элементы.
class CircularBufferArray {
private:
    int* buffer;
    int capacity;
    int size;
    int front;
    int rear;

public:

    CircularBufferArray(int capacity) {
        this->capacity = capacity;
        buffer = new int[capacity];
        size = 0;
        front = 0;
        rear = -1;
    }


    ~CircularBufferArray() {
        delete[] buffer;
    }


    bool isEmpty() {
        return size == 0;
    }


    bool isFull() {
        return size == capacity;
    }

    void enqueue(int item) {
        if (isFull()) {

            front = (front + 1) % capacity;
        } else {
            size++;
        }
        rear = (rear + 1) % capacity;
        buffer[rear] = item;
    }


    void dequeue() {
        if (isEmpty()) {
            return;
        }
        front = (front + 1) % capacity;
        size--;
    }


    int getFront() {
        if (isEmpty()) {
            return -1;
        }
        return buffer[front];
    }
};

int main() {
    {
        CircularBufferArray arr(5);

        if(arr.isEmpty()){
            std::cout << "Список пуст" << std::endl;
        }


        arr.enqueue(-24);
        arr.enqueue(5);
        arr.enqueue(1);
        arr.enqueue(0);
        arr.enqueue(17);

        if(arr.isFull()){
            std::cout << "Список полный" << std::endl;
        }


        int front = arr.getFront();
        std::cout << "Элемент в начале списка: " << front << std::endl;

        arr.dequeue();

        front = arr.getFront();
        std::cout << "Новый элемент в начале списка: " << front << std::endl;

    }
    {

        TheRing ring(5);

        if (ring.isEmpty()) {
            std::cout << "Кольцо пустое" << std::endl;
        }

        ring.enqueue(1);
        ring.enqueue(6);
        ring.enqueue(-6);
        ring.enqueue(-8);


        if (ring.isFull()) {
            std::cout << "Кольцо полное" << std::endl;
        }

        int frontRing = ring.getFront();
        std::cout << "Элемент в начале кольца: " << frontRing << std::endl;

        ring.dequeue();

        frontRing = ring.getFront();
        std::cout << "Новый элемент в начале кольца: " << frontRing << std::endl;
    }
    return 0;
}
