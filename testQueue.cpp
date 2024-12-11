#define BOOST_TEST_MODULE QueueTest
#include <boost/test/included/unit_test.hpp>
#include "../structs/queue.h"

BOOST_AUTO_TEST_SUITE(QueueTests)

BOOST_AUTO_TEST_CASE(testQueueInitialization) {
    Queue<int> queue;
    BOOST_CHECK(queue.isEmpty());
}

BOOST_AUTO_TEST_CASE(testQueuePushAndPeek) {
    Queue<int> queue;
    queue.push(1);
    BOOST_CHECK(!queue.isEmpty());
    BOOST_CHECK_EQUAL(queue.peek(), 1);
    
    queue.push(2);
    BOOST_CHECK_EQUAL(queue.peek(), 1); // Проверяем, что первый элемент все еще на месте
}

BOOST_AUTO_TEST_CASE(testQueuePop) {
    Queue<int> queue;
    queue.push(1);
    queue.push(2);
    
    queue.pop();
    BOOST_CHECK_EQUAL(queue.peek(), 2); // После удаления первого элемента, теперь должен быть второй
    
    queue.pop();
    BOOST_CHECK(queue.isEmpty()); // Теперь очередь должна быть пустой
}

BOOST_AUTO_TEST_CASE(testQueuePopEmpty) {
    Queue<int> queue;

    // Перенаправляем cerr в буфер
    std::ostringstream buffer;
    std::streambuf* oldCerr = std::cerr.rdbuf(buffer.rdbuf());

    // Вызываем pop на пустой очереди
    queue.pop();

    // Возвращаем cerr обратно
    std::cerr.rdbuf(oldCerr);

    // Проверяем вывод
    BOOST_CHECK_EQUAL(buffer.str(), "Очередь пуста. Невозможно удалить элемент.\n");
}

BOOST_AUTO_TEST_CASE(testQueuePeekEmpty) {
    Queue<int> queue;
    BOOST_CHECK_THROW(queue.peek(), std::runtime_error); // Проверяем, что выбрасывается исключение
}

BOOST_AUTO_TEST_CASE(testQueueDisplay) {
    Queue<int> queue;
    queue.push(1);
    queue.push(2);
    
    std::ostringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf()); // Перенаправляем вывод в буфер

    queue.display();

    std::cout.rdbuf(old); // Возвращаем вывод обратно

    BOOST_CHECK_EQUAL(buffer.str(), "1 2 \n"); // Проверяем правильность вывода
}

BOOST_AUTO_TEST_SUITE_END()