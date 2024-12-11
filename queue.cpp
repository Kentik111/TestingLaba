#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stdexcept>

using namespace std;

template <typename T>
class Queue {
private:
    struct Node {
        T data;
        Node* next;
        Node(T value) : data(value), next(nullptr) {}
    };

    Node* front; // Указатель на первый элемент очереди
    Node* rear;  // Указатель на последний элемент очереди

public:
    Queue();
    ~Queue();
    bool isEmpty() const;
    void push(T value);
    void pop();
    T peek() const;
    void display() const;
    // Сериализация и десериализация
    void serializeToText(const string& filename) const;
    void deserializeFromText(const string& filename);
};

template <typename T>
Queue<T>::Queue() : front(nullptr), rear(nullptr) {}

template <typename T>
Queue<T>::~Queue() {
    while (!isEmpty()) {
        pop();
    }
}

template <typename T>
bool Queue<T>::isEmpty() const {
    return front == nullptr;
}

template <typename T>
void Queue<T>::push(T value) {
    Node* newNode = new Node(value);
    if (isEmpty()) {
        front = rear = newNode;
    } else {
        rear->next = newNode;
        rear = newNode;
    }
}

template <typename T>
void Queue<T>::pop() {
    if (isEmpty()) {
        cerr << "Очередь пуста. Невозможно удалить элемент." << endl;
        return;
    }
    Node* temp = front;
    front = front->next;
    delete temp;
    if (front == nullptr) {
        rear = nullptr;
    }
}

template <typename T>
T Queue<T>::peek() const {
    if (isEmpty()) {
        throw runtime_error("Очередь пуста. Невозможно прочитать элемент.");
    }
    return front->data;
}

template <typename T>
void Queue<T>::display() const {
    Node* current = front;
    while (current) {
        cout << current->data << " ";
        current = current->next;
    }
    cout << endl;
}



// Сериализация в текстовый формат
template <>
void Queue<string>::serializeToText(const string& filename) const {
    ofstream outFile(filename);
    if (!outFile) {
        cerr << "Не удалось открыть файл для записи." << endl;
        return;
    }
    
    Node* current = front;
    while (current) {
        outFile << current->data << endl; // Записываем каждый элемент в отдельной строке
        current = current->next;
    }

    outFile.close();
}

// Десериализация из текстового формата
template <>
void Queue<string>::deserializeFromText(const string& filename) {
    ifstream inFile(filename);
    if (!inFile) {
        cerr << "Не удалось открыть файл для чтения." << endl;
        return;
    }

    while (!isEmpty()) {
        pop(); // Очищаем очередь перед загрузкой
    }

    string value;
    while (getline(inFile, value)) { // Читаем до конца файла
        push(value);
    }

    inFile.close();
}

int main() {
    Queue<string> q;

    // Добавляем элементы в очередь
    q.push("Hello");
    q.push("World");
    
    // Сериализуем очередь в текстовый файл
    q.serializeToText("queue.txt");

    // Отображаем содержимое очереди
    cout << "Содержимое очереди перед десериализацией:" << endl;
    q.display();

    // Очищаем очередь и десериализуем из файла
    q.deserializeFromText("queue.txt");

    // Отображаем содержимое очереди после десериализации
    cout << "Содержимое очереди после десериализации:" << endl;
    q.display();
}


