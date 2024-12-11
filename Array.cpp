#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stdexcept>

using namespace std;

template <typename T>
class MyArray {
private:
    T* data;
    int size;
    int capacity;

public:
    // Конструктор по умолчанию
    MyArray() : data(nullptr), size(0), capacity(0) {}

    // Конструктор с указанием начальной емкости
    MyArray(int capacity) : size(0), capacity(capacity) {
        if (capacity > 0) {
            data = new T[capacity];
        } else {
            data = nullptr;
        }
    }

    // Копирующий конструктор
    MyArray(const MyArray& other) : size(other.size), capacity(other.capacity) {
        data = new T[capacity];
        for (int i = 0; i < size; i++) {
            data[i] = other.data[i];
        }
    }

    // Оператор присваивания
    MyArray& operator=(const MyArray& other) {
        if (this != &other) {
            delete[] data;
            size = other.size;
            capacity = other.capacity;
            data = new T[capacity];
            for (int i = 0; i < size; i++) {
                data[i] = other.data[i];
            }
        }
        return *this;
    }

    // Деструктор
    ~MyArray() {
        delete[] data;
    }

    // Добавление элемента в конец массива
    void push_back(const T& value) {
        if (size == capacity) {
            resize(capacity + 1);
        }
        data[size++] = value;
    }

    // Добавление элемента по индексу
    void insert(int index, const T& value) {
        if (index < 0 || index > size) {
            throw out_of_range("Индекс за пределами массива");
        }
        if (size == capacity) {
            resize(capacity + 1);
        }
        for (int i = size; i > index; i--) {
            data[i] = data[i - 1];
        }
        data[index] = value;
        size++;
    }

    // Получение элемента по индексу
    T& operator[](int index) {
        if (index < 0 || index >= size) {
            throw out_of_range("Индекс за пределами массива");
        }
        return data[index];
    }

    // Получение элемента по индексу
    const T& operator[](int index) const {
        if (index < 0 || index >= size) {
            throw out_of_range("Индекс за пределами массива");
        }
        return data[index];
    }

    // Удаление элемента по индексу
    void erase(int index) {
        if (index < 0 || index >= size) {
            throw out_of_range("Индекс за пределами массива");
        }
        for (int i = index; i < size - 1; i++) {
            data[i] = data[i + 1];
        }
        size--;
    }

    // Замена элемента по индексу
    void replace(int index, const T& value) {
        if (index < 0 || index >= size) {
            throw out_of_range("Индекс за пределами массива");
        }
        data[index] = value;
    }

    // Длина массива
    int length() const {
        return size;
    }

    // Чтение массива (для вывода на экран)
    friend ostream& operator<<(ostream& out, const MyArray& array) {
        out << "[";
        for (int i = 0; i < array.size; i++) {
            out << array.data[i];
            if (i < array.size - 1) {
                out << ", ";
            }
        }
        out << "]";
        return out;
    }

    // Сериализация в бинарный файл
    void serializeBinary(const string& filename) const {
        ofstream file(filename, ios::binary);
        if (!file.is_open()) {
            throw runtime_error("Не удалось открыть файл для записи");
        }

        // Запись размера массива
        file.write(reinterpret_cast<const char*>(&size), sizeof(size));

        // Запись данных массива
        file.write(reinterpret_cast<const char*>(data), size * sizeof(T));

        file.close();
    }

    // Десериализация из бинарного файла
    void deserializeBinary(const string& filename) {
        ifstream file(filename, ios::binary);
        if (!file.is_open()) {
            throw runtime_error("Не удалось открыть файл для чтения");
        }

        // Чтение размера массива
        file.read(reinterpret_cast<char*>(&size), sizeof(size));

        // Выделение памяти
        resize(size); 

        // Чтение данных массива
        file.read(reinterpret_cast<char*>(data), size * sizeof(T));

        file.close();
    }


    // Сериализация в текстовый файл
    void serializeText(const string& filename) const {
        ofstream file(filename);
        if (!file.is_open()) {
            throw runtime_error("Не удалось открыть файл для записи");
        }

        file << size << endl;
        for (int i = 0; i < size; ++i) {
            file << data[i] << (i == size - 1 ? "" : " "); // Разделитель - пробел
        }
        file << endl;
        file.close();
    }

    // Десериализация из текстового файла
    void deserializeText(const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            throw runtime_error("Не удалось открыть файл для чтения");
        }

        file >> size;
        resize(size); 
        for (int i = 0; i < size; ++i) {
            file >> data[i];
        }
        file.close();
    }

private:
    // Изменение размера массива
    void resize(int newCapacity) {
        T* newData = new T[newCapacity];
        for (int i = 0; i < size; i++) {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
        capacity = newCapacity;
    }
};

int main(){
    MyArray<string> myArray(3);

    // Добавление элементов в массив
    myArray.push_back("one");
    myArray.push_back("two");
    myArray.push_back("three");
    cout << myArray << endl;
    
    myArray.serializeBinary("binarr.bin");
    myArray.serializeText("textarr.txt");
    MyArray<string> myArray2(3);
    myArray2.deserializeBinary("binarr.bin");
    cout << myArray2 << endl;
    MyArray<string> myArray3(3);
    myArray3.deserializeText("textarr.txt");
    cout << myArray3 << endl;
    return 0;
}