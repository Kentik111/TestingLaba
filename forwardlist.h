#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

//Односвязный список
// Структура узла односвязного списка
struct Node {
    string data;
    Node* next;
};

// Класс для представления односвязного списка
class forwardList {
private:


    Node* head;

public:
    // Конструктор
    forwardList();

    // Добавление элемента в голову списка
    void pushFront(string data);

    // Добавление элемента в хвост списка
    void pushBack(string data);

    // Удаление элемента с головы
    bool removeFirst();

    // Удаление элемента с хвоста
    bool removeLast();

    // Удаление элемента по значению
    bool remove(string data);

    // Поиск элемента по значению
    Node* find(string data);

    Node* getHead();

    // Вывод списка
    void print();
};

// Конструктор
forwardList::forwardList() {
    head = nullptr;
}


void forwardList::pushFront(string data) {
    Node* newNode = new Node;
    newNode->data = data;
    newNode->next = head;
    head = newNode;
}


void forwardList::pushBack(string data) {
    Node* newNode = new Node;
    newNode->data = data;
    newNode->next = nullptr;

    if (head == nullptr) {
        head = newNode;
        return;
    }

    Node* current = head;
    while (current->next != nullptr) {
        current = current->next;
    }
    current->next = newNode;
}


bool forwardList::removeFirst() {
    if (head == nullptr) {
        return false;
    }
    Node* temp = head;
    head = head->next;
    delete temp;
    return true;
}


bool forwardList::removeLast() {
    if (head == nullptr) {
        return false;
    }
    if (head->next == nullptr) {
        removeFirst();
        return true;
    }

    Node* current = head;
    while (current->next->next != nullptr) {
        current = current->next;
    }

    delete current->next;
    current->next = nullptr;
    return true;
}


bool forwardList::remove(string data) {
    if (head == nullptr) {
        return false;
    }

    if (head->data == data) {
        removeFirst();
        return true;
    }

    Node* current = head;
    while (current->next != nullptr && current->next->data != data) {
        current = current->next;
    }

    if (current->next != nullptr) {
        Node* temp = current->next;
        current->next = current->next->next;
        delete temp;
        return true;
    }
    return false;
}


Node* forwardList::find(string data) {
    Node* current = head;
    while (current != nullptr && current->data != data) {
        current = current->next;
    }
    return current;
}

Node* forwardList::getHead() {
    return head;
}

void forwardList::print() {
    Node* current = head;
    while (current != nullptr) {
        cout << current->data << " ";
        current = current->next;
    }
    cout << endl;
}
