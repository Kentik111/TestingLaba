#pragma once

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