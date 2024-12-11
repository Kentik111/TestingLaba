#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

// Структура узла
struct Node {
    string data;
    Node* next;
};

// Класс односвязного списка
class forwardList {
public:
    // Конструктор
    forwardList() {
        head = nullptr;
    }

    // Добавление элемента в начало
    void pushFront(string data) {
        Node* newNode = new Node;
        newNode->data = data;
        newNode->next = head;
        head = newNode;
    }

    // Добавление элемента в конец
    void pushBack(string data) {
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

    // Удаление первого элемента
    bool removeFirst() {
        if (head == nullptr) {
            return false;
        }
        Node* temp = head;
        head = head->next;
        delete temp;
        return true;
    }

    // Удаление последнего элемента
    bool removeLast() {
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

    // Удаление элемента по значению
    bool remove(string data) {
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

    // Поиск элемента по значению
    Node* find(string data) {
        Node* current = head;
        while (current != nullptr && current->data != data) {
            current = current->next;
        }
        return current;
    }

    // Получение указателя на головной узел
    Node* getHead() {
        return head;
    }

    // Вывод списка на консоль
    void print() {
        Node* current = head;
        while (current != nullptr) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }

    // Сериализация в бинарный файл
    void serializeBinary(const string& filename) {
        ofstream file(filename, ios::binary);
        if (!file.is_open()) {
            cerr << "Error opening file for binary serialization." << endl;
            return;
        }

        Node* current = head;
        while (current != nullptr) {
            int len = current->data.length();
            file.write(reinterpret_cast<const char*>(&len), sizeof(int));
            file.write(current->data.c_str(), len);
            current = current->next;
        }
        file.close();
    }

    // Десериализация из бинарного файла
    void deserializeBinary(const string& filename) {
        ifstream file(filename, ios::binary);
        if (!file.is_open()) {
            cerr << "Error opening file for binary deserialization." << endl;
            return;
        }

        clear(); // Очищаем существующий список

        while (true) {
            int len;
            file.read(reinterpret_cast<char*>(&len), sizeof(int));
            if (file.eof()) break;

            char* data = new char[len + 1];
            file.read(data, len);
            data[len] = '\0';
            pushBack(data);
            delete[] data;
        }
        file.close();
    }


    // Сериализация в текстовый файл
    void serializeText(const string& filename) {
        ofstream file(filename);
        if (!file.is_open()) {
            cerr << "Error opening file for text serialization." << endl;
            return;
        }

        Node* current = head;
        while (current != nullptr) {
            file << current->data << (current->next != nullptr ? "," : "");
            current = current->next;
        }
        file << endl;
        file.close();
    }

    // Десериализация из текстового файла
    void deserializeText(const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            cerr << "Error opening file for text deserialization." << endl;
            return;
        }

        clear(); // Очищаем существующий список
        string line;
        getline(file, line);

        stringstream ss(line);
        string item;
        while (getline(ss, item, ',')) {
            pushBack(item);
        }
        file.close();
    }

    // Очистка списка
    void clear() {
        Node* current = head;
        while (current != nullptr) {
            Node* next = current->next;
            delete current;
            current = next;
        }
        head = nullptr;
    }

private:
    Node* head;
};


int main() {
    forwardList list;
    list.pushBack("one");
    list.pushBack("two");
    list.pushBack("three");
    list.print(); // one two three

    list.serializeBinary("list.bin");
    list.serializeText("list.txt");

    forwardList list2;
    list2.deserializeBinary("list.bin");
    list2.print(); // one two three

    forwardList list3;
    list3.deserializeText("list.txt");
    list3.print(); // one two three

    list.clear();
    list2.clear();
    list3.clear();
    return 0;
}
