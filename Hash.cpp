#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

template <typename KeyType, typename ValueType>
class HashNode {
public:
    KeyType key;
    ValueType value;
    HashNode* next;

    HashNode(const KeyType& key, const ValueType& value);
};

template <typename KeyType, typename ValueType>
class HashTable {
private:
    size_t size;
    HashNode<KeyType, ValueType>** table;

    size_t hash(const KeyType& key) const;

public:
    HashTable(size_t initialSize = 10);
    ~HashTable();

    void insert(const KeyType& key, const ValueType& value);
    ValueType get(const KeyType& key) const;
    void remove(const KeyType& key);
    bool contains(const KeyType& key) const;
    size_t getSize() const;
    HashNode<KeyType, ValueType>* getNodeAtIndex(size_t index) const;
    void print() const;

    // Сериализация и десериализация
    void serializeToText(const string& filename) const;
    void deserializeFromText(const string& filename);
};

template <typename KeyType, typename ValueType>
HashNode<KeyType, ValueType>::HashNode(const KeyType& key, const ValueType& value)
    : key(key), value(value), next(nullptr) {}

template <typename KeyType, typename ValueType>
HashTable<KeyType, ValueType>::HashTable(size_t initialSize)
    : size(initialSize), table(new HashNode<KeyType, ValueType>*[size]) {
    for (size_t i = 0; i < size; ++i) {
        table[i] = nullptr;
    }
}

template <typename KeyType, typename ValueType>
HashTable<KeyType, ValueType>::~HashTable() {
    for (size_t i = 0; i < size; ++i) {
        HashNode<KeyType, ValueType>* current = table[i];
        while (current != nullptr) {
            HashNode<KeyType, ValueType>* temp = current;
            current = current->next;
            delete temp;
        }
    }
    delete[] table;
}

template <typename KeyType, typename ValueType>
size_t HashTable<KeyType, ValueType>::hash(const KeyType& key) const {
    return std::hash<KeyType>()(key) % size;
}

template <typename KeyType, typename ValueType>
void HashTable<KeyType, ValueType>::insert(const KeyType& key, const ValueType& value) {
    size_t index = hash(key);
    HashNode<KeyType, ValueType>* newNode = new HashNode<KeyType, ValueType>(key, value);
    newNode->next = table[index];
    table[index] = newNode;
}

template <typename KeyType, typename ValueType>
ValueType HashTable<KeyType, ValueType>::get(const KeyType& key) const {
    size_t index = hash(key);
    HashNode<KeyType, ValueType>* current = table[index];
    while (current != nullptr) {
        if (current->key == key) {
            return current->value;
        }
        current = current->next;
    }
    throw std::out_of_range("Ключ не найден в хеш-таблице");
}

template <typename KeyType, typename ValueType>
void HashTable<KeyType, ValueType>::remove(const KeyType& key) {
    size_t index = hash(key);
    HashNode<KeyType, ValueType>* current = table[index];
    HashNode<KeyType, ValueType>* previous = nullptr;
    while (current != nullptr) {
        if (current->key == key) {
            if (previous == nullptr) {
                table[index] = current->next;
            } else {
                previous->next = current->next;
            }
            delete current;
            return;
        }
        previous = current;
        current = current->next;
    }
}

template <typename KeyType, typename ValueType>
void HashTable<KeyType, ValueType>::print() const {
    for (size_t i = 0; i < size; ++i) {
        cout << "Индекс " << i << ": ";
                HashNode<KeyType, ValueType>* current = table[i];
        while (current != nullptr) {
            cout << "(" << current->key << ", " << current->value << ") ";
            current = current->next;
        }
        cout << endl;
    }
}

template <typename KeyType, typename ValueType>
void HashTable<KeyType, ValueType>::serializeToText(const string& filename) const {
    ofstream file(filename);
    if (!file.is_open()) {
        throw runtime_error("Не удалось открыть файл для записи");
    }

    for (size_t i = 0; i < size; ++i) {
        HashNode<KeyType, ValueType>* current = table[i];
        while (current != nullptr) {
            file << current->key << " " << current->value << endl;
            current = current->next;
        }
    }

    file.close();
}

template <typename KeyType, typename ValueType>
void HashTable<KeyType, ValueType>::deserializeFromText(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        throw runtime_error("Не удалось открыть файл для чтения");
    }

    KeyType key;
    ValueType value;
    
    while (file >> key >> value) {
        insert(key, value);
    }

    file.close();
}

int main(){
    HashTable<string, string> ht(3);

    ht.insert("one", "Who");
    ht.insert("two", "Am");
    ht.insert("three", "I");


    ht.print();

    ht.serializeToText("hash.txt");

    HashTable<string, string> ht2(3);
    ht2.deserializeFromText("hash.txt");
    ht2.print();

}