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

/*BOOST_AUTO_TEST_SUITE(forwardListTests)

BOOST_AUTO_TEST_CASE(test_pushFront) {
    forwardList list;
    list.pushFront("a");
    BOOST_CHECK_EQUAL(list.getHead()->data, "a");
    
    list.pushFront("b");
    BOOST_CHECK_EQUAL(list.getHead()->data, "b");
    BOOST_CHECK_EQUAL(list.getHead()->next->data, "a");
    
    list.pushFront("c");
    BOOST_CHECK_EQUAL(list.getHead()->data, "c");
    BOOST_CHECK_EQUAL(list.getHead()->next->data, "b");
}

BOOST_AUTO_TEST_CASE(test_pushBack) {
    forwardList list;
    list.pushBack("a");
    BOOST_CHECK_EQUAL(list.getHead()->data, "a");
    
    list.pushBack("b");
    BOOST_CHECK_EQUAL(list.getHead()->next->data, "b");
    
    list.pushBack("c");
    BOOST_CHECK_EQUAL(list.getHead()->next->next->data, "c");
}

BOOST_AUTO_TEST_CASE(test_removeFirst) {
    forwardList list;
    list.pushFront("a");
    list.pushFront("b");
    
    BOOST_CHECK(list.removeFirst());
    BOOST_CHECK_EQUAL(list.getHead()->data, "a");
    
    BOOST_CHECK(list.removeFirst());
    BOOST_CHECK(list.getHead() == nullptr); 
    
    BOOST_CHECK(!list.removeFirst()); // Удаление из пустого списка
}

BOOST_AUTO_TEST_CASE(test_removeLast) {
    forwardList list;
    list.pushBack("a");
    list.pushBack("b");
    
    BOOST_CHECK(list.removeLast());
    BOOST_CHECK_EQUAL(list.getHead()->data, "a");
    
    BOOST_CHECK(list.removeLast());
    BOOST_CHECK(list.getHead() == nullptr);
    
    BOOST_CHECK(!list.removeLast()); // Удаление из пустого списка
}

BOOST_AUTO_TEST_CASE(test_remove) {
    forwardList list;
    list.pushBack("a");
    list.pushBack("b");
    list.pushBack("c");
    
    BOOST_CHECK(list.remove("b"));
    BOOST_CHECK_EQUAL(list.getHead()->data, "a");
    BOOST_CHECK_EQUAL(list.getHead()->next->data, "c");
    
    BOOST_CHECK(!list.remove("d")); // Попытка удалить несуществующий элемент
}

BOOST_AUTO_TEST_CASE(test_find) {
    forwardList list;
    list.pushBack("a");
    list.pushBack("b");
    list.pushBack("c");

    BOOST_CHECK_EQUAL(list.find("b")->data, "b");
    BOOST_CHECK(list.find("d") == nullptr); // Поиск несуществующего элемента
}

BOOST_AUTO_TEST_CASE(test_removeFromEmptyList) {
    forwardList list;
    
    // Проверяем удаление из пустого списка
    BOOST_CHECK(!list.removeFirst());
    BOOST_CHECK(!list.removeLast());
}

BOOST_AUTO_TEST_CASE(test_removeFirstFromSingleElementList) {
    forwardList list;
    list.pushFront("a");

    // Проверяем удаление первого элемента из списка с одним элементом
    BOOST_CHECK(list.removeFirst());
    BOOST_CHECK(list.getHead() == nullptr);
}

BOOST_AUTO_TEST_CASE(test_removeLastFromSingleElementList) {
    forwardList list;
    list.pushFront("a");

    // Проверяем удаление последнего элемента из списка с одним элементом
    BOOST_CHECK(list.removeLast());
    BOOST_CHECK(list.getHead() == nullptr);
}

BOOST_AUTO_TEST_CASE(test_multipleRemovals) {
    forwardList list;
    list.pushBack("a");
    list.pushBack("b");
    list.pushBack("c");

    // Удаляем все элементы по одному
    BOOST_CHECK(list.remove("a"));
    BOOST_CHECK_EQUAL(list.getHead()->data, "b");

    BOOST_CHECK(list.remove("b"));
        BOOST_CHECK_EQUAL(list.getHead()->data, "c");

    BOOST_CHECK(list.remove("c"));
    BOOST_CHECK(list.getHead() == nullptr);
}

BOOST_AUTO_TEST_CASE(test_pushPopSequence) {
    forwardList list;

    // Последовательное добавление и удаление элементов
    list.pushBack("x");
    list.pushBack("y");
    
    BOOST_CHECK_EQUAL(list.getHead()->data, "x");
    
    // Удаляем первый элемент
    list.removeFirst();
    
    BOOST_CHECK_EQUAL(list.getHead()->data, "y");

    // Удаляем последний элемент
    list.removeLast();
    
    BOOST_CHECK(list.getHead() == nullptr);
}

BOOST_AUTO_TEST_CASE(test_removeNonExistentElement) {
    forwardList list;
    
    // Проверяем попытку удалить несуществующий элемент
    list.pushBack("a");
    
    // Удаляем существующий элемент
    BOOST_CHECK(list.remove("a"));
    
    // Проверяем попытку удалить уже удаленный элемент
    BOOST_CHECK(!list.remove("a"));
}

BOOST_AUTO_TEST_CASE(test_findOnEmptyList) {
    forwardList list;

    // Проверяем поиск на пустом списке
    BOOST_CHECK(list.find("a") == nullptr);
}

BOOST_AUTO_TEST_CASE(test_findMultipleElements) {
    forwardList list;
    
    // Добавляем несколько элементов
    list.pushBack("1");
    list.pushBack("2");
    
    // Проверяем поиск каждого элемента
    BOOST_CHECK_EQUAL(list.find("1")->data, "1");
    BOOST_CHECK_EQUAL(list.find("2")->data, "2");
}

BOOST_AUTO_TEST_CASE(test_multipleAddRemoveSequence) {
    forwardList list;
    
    // Последовательное добавление и удаление элементов
    list.pushBack("a");
    list.pushBack("b");
    list.pushBack("c");
    
    // Удаляем один элемент
    BOOST_CHECK(list.remove("b"));
    BOOST_CHECK_EQUAL(list.getHead()->data, "a");
    BOOST_CHECK_EQUAL(list.getHead()->next->data, "c");
    
    // Удаляем другой элемент
    BOOST_CHECK(list.remove("a"));
    BOOST_CHECK_EQUAL(list.getHead()->data, "c");
    
    // Удаляем последний элемент
    BOOST_CHECK(list.remove("c"));
    BOOST_CHECK(list.getHead() == nullptr);
}

BOOST_AUTO_TEST_CASE(test_emptyListAfterMultipleRemovals) {
    forwardList list;

    // Добавляем элементы
    list.pushBack("1");
    list.pushBack("2");
    
    // Удаляем все элементы
    BOOST_CHECK(list.remove("1"));
    BOOST_CHECK(list.remove("2"));
    
    // Проверяем, что список пуст
    BOOST_CHECK(list.getHead() == nullptr);
}

BOOST_AUTO_TEST_CASE(test_removeFromSingleElementListTwice) {
    forwardList list;
    
    // Добавляем один элемент
    list.pushFront("single");

    // Удаляем первый элемент
    BOOST_CHECK(list.removeFirst());
    
    // Проверяем, что список пуст
    BOOST_CHECK(list.getHead() == nullptr);
    
    // Проверяем удаление из пустого списка
    BOOST_CHECK(!list.removeFirst());
}

BOOST_AUTO_TEST_CASE(test_pushFrontAndRemove) {
    forwardList list;

    // Добавляем элементы с pushFront
    list.pushFront("first");
    list.pushFront("second");

    // Удаляем первый элемент
    BOOST_CHECK(list.remove("second"));
    
    // Проверяем состояние списка
    BOOST_CHECK_EQUAL(list.getHead()->data, "first");
}

BOOST_AUTO_TEST_CASE(test_pushBackAndRemove) {
    forwardList list;

    // Добавляем элементы с pushBack
    list.pushBack("first");
    list.pushBack("second");

    // Удаляем последний элемент
    BOOST_CHECK(list.remove("second"));

    // Проверяем состояние списка
     BOOST_CHECK_EQUAL(list.getHead()->data, "first");
}

BOOST_AUTO_TEST_CASE(test_removeNullElement) {
    forwardList list;

    // Проверяем удаление null-элемента (если это поддерживается)
    BOOST_CHECK(!list.remove(""));
}

BOOST_AUTO_TEST_CASE(test_findOnSingleElementList) {
    forwardList list;
    
    // Добавляем один элемент
    list.pushFront("only");

    // Проверяем поиск этого элемента
    BOOST_CHECK_EQUAL(list.find("only")->data, "only");
}

BOOST_AUTO_TEST_SUITE_END()*/



