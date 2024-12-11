#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

// Структура для узла двусвязного списка
struct NodeDouble {
    string data;
    NodeDouble* prev;
    NodeDouble* next;
};

// Класс для реализации двусвязного списка
class DoublyLinkedList {
private:
    NodeDouble* head;
    NodeDouble* tail;

public:
    // Конструктор
    DoublyLinkedList();

    // Добавление элемента в голову списка
    void pushFront(string data);

    // Добавление элемента в хвост списка
    void pushBack(string data);

    // Удаление элемента с головы списка
    bool popFront();

    // Удаление элемента с хвоста списка
    bool popBack();

    // Удаление элемента по значению
    bool remove(string data);

    // Поиск элемента по значению
    NodeDouble* find(string data);

    NodeDouble* getHead();

    // Чтение списка
    void print();
};

DoublyLinkedList::DoublyLinkedList() {
    head = nullptr;
    tail = nullptr;
}

void DoublyLinkedList::pushFront(std::string data) {
    NodeDouble* newNode = new NodeDouble;
    newNode->data = data;
    newNode->prev = nullptr;
    newNode->next = head;

    if (head != nullptr) {
        head->prev = newNode;
    }

    head = newNode;
    if (tail == nullptr) {
        tail = newNode;
    }
}

void DoublyLinkedList::pushBack(string data) {
    NodeDouble* newNode = new NodeDouble;
    newNode->data = data;
    newNode->next = nullptr;
    newNode->prev = tail;

    if (tail != nullptr) {
        tail->next = newNode;
    }

    tail = newNode;
    if (head == nullptr) {
        head = newNode;
    }
}

bool DoublyLinkedList::popFront() {
    if (head == nullptr) {
        return false;
    }

    NodeDouble* temp = head;
    head = head->next;

    if (head != nullptr) {
        head->prev = nullptr;
    } else {
        tail = nullptr;
    }

    delete temp;
    return true;
}

bool DoublyLinkedList::popBack() {
    if (tail == nullptr) {
        return false;
    }

    NodeDouble* temp = tail;
    tail = tail->prev;

    if (tail != nullptr) {
        tail->next = nullptr;
    } else {
        head = nullptr;
    }

    delete temp;
    return true;
}

bool DoublyLinkedList::remove(string data) {
    if (head == nullptr) { // Список пуст
        return false;
    }
    NodeDouble* current = head;
    while (current != nullptr) {
        if (current->data == data) {
            if (current == head) {
                popFront();
                return true;
            } else if (current == tail) {
                popBack();
                return true;
            } else {
                current->prev->next = current->next;
                current->next->prev = current->prev;
                delete current;
                return true;
            }
        }
        current = current->next;
    }
    return false;
}

NodeDouble* DoublyLinkedList::find(string data) {
    NodeDouble* current = head;
    while (current != nullptr) {
        if (current->data == data) {
            return current;
        }
        current = current->next;
    }
    return nullptr;
}

NodeDouble* DoublyLinkedList::getHead() {
    return head;
}

void DoublyLinkedList::print() {
    NodeDouble* current = head;
    while (current != nullptr) {
        cout << current->data << " ";
        current = current->next;
    }
    cout << endl;
}