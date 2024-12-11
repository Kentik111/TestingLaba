#define BOOST_TEST_MODULE ArrayTest
#include <boost/test/included/unit_test.hpp>
#include "../structs/Array.h"

BOOST_AUTO_TEST_SUITE(ArrayTests)

BOOST_AUTO_TEST_CASE(default_constructor) {
    MyArray<int> arr;
    BOOST_CHECK_EQUAL(arr.length(), 0);
}

BOOST_AUTO_TEST_CASE(capacity_constructor) {
    MyArray<int> arr(5);
    BOOST_CHECK_EQUAL(arr.length(), 0);
}

BOOST_AUTO_TEST_CASE(copy_constructor) {
    MyArray<int> arr(5);
    arr.push_back(1);
    arr.push_back(2);
    MyArray<int> arr_copy(arr);
    BOOST_CHECK_EQUAL(arr_copy.length(), 2);
    BOOST_CHECK_EQUAL(arr_copy[0], 1);
    BOOST_CHECK_EQUAL(arr_copy[1], 2);
}

BOOST_AUTO_TEST_CASE(assignment_operator) {
    MyArray<int> arr(5);
    arr.push_back(1);
    arr.push_back(2);
    MyArray<int> arr_assigned;
    arr_assigned = arr;
    BOOST_CHECK_EQUAL(arr_assigned.length(), 2);
    BOOST_CHECK_EQUAL(arr_assigned[0], 1);
    BOOST_CHECK_EQUAL(arr_assigned[1], 2);
}

BOOST_AUTO_TEST_CASE(push_back_and_access) {
    MyArray<int> arr;
    arr.push_back(10);
    arr.push_back(20);
    BOOST_CHECK_EQUAL(arr.length(), 2);
    BOOST_CHECK_EQUAL(arr[0], 10);
    BOOST_CHECK_EQUAL(arr[1], 20);
}

BOOST_AUTO_TEST_CASE(insert) {
    MyArray<int> arr;
    arr.push_back(1);
    arr.push_back(3);
    arr.insert(1, 2); // Вставляем 2 на индекс 1
    BOOST_CHECK_EQUAL(arr.length(), 3);
    BOOST_CHECK_EQUAL(arr[0], 1);
    BOOST_CHECK_EQUAL(arr[1], 2);
    BOOST_CHECK_EQUAL(arr[2], 3);
}

BOOST_AUTO_TEST_CASE(erase) {
    MyArray<int> arr;
    arr.push_back(1);
    arr.push_back(2);
    arr.push_back(3);
    arr.erase(1); // Удаляем элемент на индексе 1
    BOOST_CHECK_EQUAL(arr.length(), 2);
    BOOST_CHECK_EQUAL(arr[0], 1);
    BOOST_CHECK_EQUAL(arr[1], 3);
}

BOOST_AUTO_TEST_CASE(replace) {
    MyArray<int> arr;
    arr.push_back(1);
    arr.push_back(2);
    arr.replace(1, 3); // Заменяем элемент на индексе 1
    BOOST_CHECK_EQUAL(arr[1], 3);
}

BOOST_AUTO_TEST_CASE(out_of_range_access) {
    MyArray<int> arr;
    arr.push_back(1);
    
    BOOST_CHECK_THROW(arr[-1], std::out_of_range); // Проверка на выход за пределы
    BOOST_CHECK_THROW(arr[1], std::out_of_range); // Проверка на выход за пределы
}

BOOST_AUTO_TEST_CASE(out_of_range_insert) {
    MyArray<int> arr;
    BOOST_CHECK_THROW(arr.insert(-1, 10), std::out_of_range); // Проверка на выход за пределы
}

BOOST_AUTO_TEST_CASE(out_of_range_erase) {
    MyArray<int> arr;
    arr.push_back(1);
    BOOST_CHECK_THROW(arr.erase(1), std::out_of_range); // Проверка на выход за пределы
}

BOOST_AUTO_TEST_CASE(resize) {
    MyArray<int> arr;
    for (int i = 0; i < 10; i++) {
        arr.push_back(i);
    }
    
    BOOST_CHECK_EQUAL(arr.length(), 10);

    // Проверка, что элементы остались на месте после изменения размера
    for (int i = 0; i < 10; i++) {
        BOOST_CHECK_EQUAL(arr[i], i);
    }
}

BOOST_AUTO_TEST_SUITE_END()