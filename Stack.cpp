#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stdexcept>
using namespace std;

template<typename T>
class Stack {
public:
    Stack();
    ~Stack();

    bool isEmpty() const;
    void push(T value);
    void pop();
    T top() const;
    void print() const;

    // Сериализация и десериализация
    void serialize(const string& file_name) const;
    void deserialize(const string& file_name);

private:
    struct Node;
    Node* topNode;
};

template<typename T>
struct Stack<T>::Node {
    T data;
    Node* next;
    Node(T value) : data(value), next(nullptr) {}
};

template<typename T>
Stack<T>::Stack() : topNode(nullptr) {}

template<typename T>
Stack<T>::~Stack() {
    while (!isEmpty()) {
        pop();
    }
}

template<typename T>
bool Stack<T>::isEmpty() const {
    return topNode == nullptr;
}

template<typename T>
void Stack<T>::push(T value) {
    Node* newNode = new Node(value);
    newNode->next = topNode;
    topNode = newNode;
}

template<typename T>
void Stack<T>::pop() {
    if (isEmpty()) {
        cerr << "Стек пуст. Невозможно удалить элемент." << endl;
        return;
    }
    Node* temp = topNode;
    topNode = topNode->next;
    delete temp;
}

template<typename T>
T Stack<T>::top() const {
    if (isEmpty()) {
        throw runtime_error("Стек пуст. Невозможно прочитать элемент.");
    }
    return topNode->data;
}

template<typename T>
void Stack<T>::print() const {
    Node* current = topNode;
    while (current) {
        cout << current->data << " ";
        current = current->next;
    }
    cout << endl;
}

// Сериализация
template<>
void Stack<string>::serialize(const string& file_name) const {
    ofstream out(file_name, ios::binary);
    if (!out) {
        cerr << "Ошибка открытия файла для записи." << endl;
        return;
    }

    Node* current = topNode;
    while (current != nullptr) {
        size_t len = current->data.size();
        out.write(reinterpret_cast<char*>(&len), sizeof(len)); // Записываем длину строки
        out.write(current->data.c_str(), len); // Записываем строку
        current = current->next;
    }

    out.close();
}

// Десериализация
template<>
void Stack<string>::deserialize(const string& file_name) {
    ifstream in(file_name, ios::binary);
    if (!in) {
        cerr << "Ошибка открытия файла для чтения." << endl;
        return;
    }

    // Очищаем стек
    while (!isEmpty()) {
        pop();
    }

    while (true) {
        size_t len;
        if (!in.read(reinterpret_cast<char*>(&len), sizeof(len))) break; // Читаем длину строки
        string value(len, '0'); // Создаем строку нужной длины
        if (!in.read(&value[0], len)) break; // Читаем строку
        push(value); // Добавляем строку в стек
    }

    in.close();
}

int main() {
    Stack<string> myStack;

    myStack.push("Hello");
    myStack.push("World");

    myStack.print();

    myStack.serialize("stack_data.bin");

    Stack<string> newStack;
    newStack.deserialize("stack_data.bin");

    newStack.print(); 

    return 0;
}

