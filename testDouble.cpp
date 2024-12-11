#define BOOST_TEST_MODULE doublyListTest
#include <boost/test/included/unit_test.hpp>
#include "../structs/doubleList.h"

BOOST_AUTO_TEST_SUITE(DoublyLinkedListTests)

BOOST_AUTO_TEST_CASE(testPushFront) {
    DoublyLinkedList list;
    list.pushFront("first");
    BOOST_CHECK_EQUAL(list.getHead()->data, "first");
    
    list.pushFront("second");
    BOOST_CHECK_EQUAL(list.getHead()->data, "second");
    BOOST_CHECK_EQUAL(list.getHead()->next->data, "first");
}

BOOST_AUTO_TEST_CASE(testPushBack) {
    DoublyLinkedList list;
    list.pushBack("first");
    BOOST_CHECK_EQUAL(list.getHead()->data, "first");
    
    list.pushBack("second");
    BOOST_CHECK_EQUAL(list.getHead()->next->data, "second");
}

BOOST_AUTO_TEST_CASE(testPopFront) {
    DoublyLinkedList list;
    list.pushFront("first");
    list.pushFront("second");
    
    BOOST_CHECK(list.popFront());
    BOOST_CHECK_EQUAL(list.getHead()->data, "first");
    
    BOOST_CHECK(list.popFront());
    BOOST_CHECK(list.getHead() == nullptr);
    
    BOOST_CHECK(!list.popFront()); // Проверка на пустом списке
}

BOOST_AUTO_TEST_CASE(testPopBack) {
    DoublyLinkedList list;
    list.pushBack("first");
    list.pushBack("second");
    
    BOOST_CHECK(list.popBack());
    BOOST_CHECK_EQUAL(list.getHead()->data, "first");
    
    BOOST_CHECK(list.popBack());
    BOOST_CHECK(list.getHead() == nullptr);
    
    BOOST_CHECK(!list.popBack()); // Проверка на пустом списке
}

BOOST_AUTO_TEST_CASE(testRemove) {
    DoublyLinkedList list;
    list.pushBack("first");
    list.pushBack("second");
    list.pushBack("third");

    BOOST_CHECK(list.remove("second"));
    BOOST_CHECK_EQUAL(list.getHead()->next->data, "third");

    BOOST_CHECK(list.remove("first"));
    BOOST_CHECK_EQUAL(list.getHead()->data, "third");

    BOOST_CHECK(list.remove("third"));
    BOOST_CHECK(list.getHead() == nullptr);

    BOOST_CHECK(!list.remove("fourth")); // Удаление несуществующего элемента
}

BOOST_AUTO_TEST_CASE(testFind) {
    DoublyLinkedList list;
    list.pushBack("first");
    list.pushBack("second");

    BOOST_CHECK(list.find("first") != nullptr);
    BOOST_CHECK(list.find("second") != nullptr);
    BOOST_CHECK(list.find("third") == nullptr); // Не найденный элемент
}

BOOST_AUTO_TEST_CASE(testPrint) {
    DoublyLinkedList list;
    list.pushBack("first");
    list.pushBack("second");

    BOOST_CHECK_NO_THROW(list.print());
}

BOOST_AUTO_TEST_CASE(test_emptyList) {
    DoublyLinkedList list;

    BOOST_CHECK(!list.popFront()); // Удаление из пустого списка
    BOOST_CHECK(!list.popBack());  // Удаление из пустого списка
    BOOST_CHECK(!list.remove("any"));  // Удаление из пустого списка
}

BOOST_AUTO_TEST_SUITE_END()

