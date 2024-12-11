#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

struct NodeDouble {
    string data;
    NodeDouble* prev;
    NodeDouble* next;
};

class DoublyLinkedList {
public:
    DoublyLinkedList() : head(nullptr), tail(nullptr) {}

    ~DoublyLinkedList() {
        NodeDouble* current = head;
        while (current != nullptr) {
            NodeDouble* next = current->next;
            delete current;
            current = next;
        }
    }

    void pushFront(const string& data) {
        NodeDouble* newNode = new NodeDouble{data, nullptr, head};
        if (head) head->prev = newNode;
        head = newNode;
        if (!tail) tail = newNode;
    }

    void pushBack(const string& data) {
        NodeDouble* newNode = new NodeDouble{data, tail, nullptr};
        if (tail) tail->next = newNode;
        tail = newNode;
        if (!head) head = newNode;
    }

    bool popFront() {
        if (!head) return false;
        NodeDouble* temp = head;
        head = head->next;
        if (head) head->prev = nullptr;
        else tail = nullptr;
        delete temp;
        return true;
    }

    bool popBack() {
        if (!tail) return false;
        NodeDouble* temp = tail;
        tail = tail->prev;
        if (tail) tail->next = nullptr;
        else head = nullptr;
        delete temp;
        return true;
    }

    bool remove(const string& data) {
        NodeDouble* current = head;
        while (current) {
            if (current->data == data) {
                if (current == head) popFront();
                else if (current == tail) popBack();
                else {
                    current->prev->next = current->next;
                    current->next->prev = current->prev;
                }
                delete current;
                return true;
            }
            current = current->next;
        }
        return false;
    }

    void print() const {
        NodeDouble* current = head;
        while (current) {
            cout << current->data << (current->next ? " " : "");
            current = current->next;
        }
        cout << endl;
    }

    void serializeBinary(const string& filename) const {
        ofstream file(filename, ios::binary);
        if (!file.is_open()) throw runtime_error("Не удалось открыть файл для записи");
        NodeDouble* current = head;
        while (current) {
            size_t len = current->data.length();
            file.write(reinterpret_cast<const char*>(&len), sizeof(size_t));
            file.write(current->data.c_str(), len);
            current = current->next;
        }
        file.close();
    }

    void serializeText(const string& filename) const {
        ofstream file(filename);
        if (!file.is_open()) throw runtime_error("Не удалось открыть файл для записи");
        NodeDouble* current = head;
        while (current) {
            file << current->data << (current->next ? "," : "");
            current = current->next;
        }
        file << endl;
        file.close();
    }

    void deserializeBinary(const string& filename) {
        ifstream file(filename, ios::binary);
        if (!file.is_open()) throw runtime_error("Не удалось открыть файл для чтения");
        while (true) {
            size_t len;
            file.read(reinterpret_cast<char*>(&len), sizeof(size_t));
            if (file.gcount() != sizeof(size_t)) break;
            char* data = new char[len + 1];
            file.read(data, len);
            data[len] = '\0';
            pushBack(data);
            delete[] data;
        }
        file.close();
    }

    void deserializeText(const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) throw runtime_error("Не удалось открыть файл для чтения");
        string line;
        getline(file, line);
        stringstream ss(line);
        string item;
        while (getline(ss, item, ',')) {
            pushBack(item);
        }
        file.close();
    }

private:
    NodeDouble* head;
    NodeDouble* tail;
};

int main() {
    DoublyLinkedList list;
    list.pushBack("one");
    list.pushBack("two");
    list.pushBack("three");
    list.print(); // one two three

    try {
        list.serializeBinary("binary.bin");
        list.serializeText("text.txt");
    } catch (const runtime_error& error) {
        cerr << "Ошибка сериализации: " << error.what() << endl;
        return 1;
    }

    DoublyLinkedList list2;
    try {
        list2.deserializeBinary("binary.bin");
        list2.print(); // one two three
        DoublyLinkedList list3;
        list3.deserializeText("text.txt");
        list3.print(); // one two three
    } catch (const runtime_error& error) {
        cerr << "Ошибка десериализации: " << error.what() << endl;
        return 1;
    }

    return 0;
}
