#define BOOST_TEST_MODULE ListTest
#include <boost/test/included/unit_test.hpp>
#include "../structs/forwardlist.h"

BOOST_AUTO_TEST_CASE(test_pushFront) {
    forwardList list;
    list.pushFront("first");
    list.pushFront("second");

    BOOST_CHECK_EQUAL(list.getHead()->data, "second");
    BOOST_CHECK_EQUAL(list.getHead()->next->data, "first");
}

BOOST_AUTO_TEST_CASE(test_pushBack) {
    forwardList list;
    list.pushBack("first");
    list.pushBack("second");

    BOOST_CHECK_EQUAL(list.getHead()->data, "first");
    BOOST_CHECK_EQUAL(list.getHead()->next->data, "second");
}

BOOST_AUTO_TEST_CASE(test_removeFirst) {
    forwardList list;
    list.pushFront("first");
    list.pushFront("second");

    BOOST_CHECK(list.removeFirst());
    BOOST_CHECK_EQUAL(list.getHead()->data, "first");
}

BOOST_AUTO_TEST_CASE(test_removeLast) {
    forwardList list;
    list.pushBack("first");
    list.pushBack("second");

    BOOST_CHECK(list.removeLast());
    BOOST_CHECK_EQUAL(list.getHead()->data, "first");
    BOOST_CHECK(list.removeLast());
    BOOST_CHECK(!list.removeLast()); // Список пуст
}

BOOST_AUTO_TEST_CASE(test_removeByValue) {
    forwardList list;
    list.pushBack("first");
    list.pushBack("second");
    list.pushBack("third");

    BOOST_CHECK(list.remove("second"));
    BOOST_CHECK_EQUAL(list.getHead()->next->data, "third");
    
    BOOST_CHECK(!list.remove("fourth")); // Элемент не существует
}

BOOST_AUTO_TEST_CASE(test_find) {
    forwardList list;
    list.pushBack("first");
    list.pushBack("second");

    BOOST_CHECK(list.find("first") != nullptr);
    BOOST_CHECK(list.find("second") != nullptr);
    BOOST_CHECK(list.find("third") == nullptr); // Элемент не существует
}

BOOST_AUTO_TEST_CASE(test_print) {
    // Для тестирования вывода можно использовать стандартный вывод или перенаправление потока.
    // Здесь мы просто проверим, что метод print не вызывает ошибок.
    forwardList list;
    list.pushBack("first");
    list.pushBack("second");

    BOOST_CHECK_NO_THROW(list.print());
}

BOOST_AUTO_TEST_CASE(test_emptyList) {
    forwardList list;

    BOOST_CHECK(!list.removeFirst()); // Удаление из пустого списка
    BOOST_CHECK(!list.removeLast());  // Удаление из пустого списка
    BOOST_CHECK(!list.remove("any"));  // Удаление из пустого списка
}




