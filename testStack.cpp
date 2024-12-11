#define BOOST_TEST_MODULE StackTest
#include <boost/test/included/unit_test.hpp>
#include "../structs/stack.h"

BOOST_AUTO_TEST_SUITE(StackTests)

BOOST_AUTO_TEST_CASE(testPushAndTop) {
    Stack<int> stack;
    stack.push(1);
    stack.push(2);
    
    BOOST_CHECK_EQUAL(stack.top(), 2);
    
    stack.push(3);
    BOOST_CHECK_EQUAL(stack.top(), 3);
}

BOOST_AUTO_TEST_CASE(testPop) {
    Stack<int> stack;
    stack.push(1);
    stack.push(2);
    
    stack.pop();
    BOOST_CHECK_EQUAL(stack.top(), 1);
    
    stack.pop();
    BOOST_CHECK(stack.isEmpty());
}

BOOST_AUTO_TEST_CASE(testIsEmpty) {
    Stack<int> stack;
    BOOST_CHECK(stack.isEmpty());
    
    stack.push(1);
    BOOST_CHECK(!stack.isEmpty());
    
    stack.pop();
    BOOST_CHECK(stack.isEmpty());
}

BOOST_AUTO_TEST_CASE(testTopException) {
    Stack<int> stack;
    
    BOOST_CHECK_THROW(stack.top(), std::runtime_error);
}

BOOST_AUTO_TEST_CASE(testPopFromEmptyStack) {
    Stack<int> stack;

    
    std::streambuf* oldCerr = std::cerr.rdbuf();
    std::ostringstream oss;
    std::cerr.rdbuf(oss.rdbuf());

    stack.pop();
    
    
    std::cerr.rdbuf(oldCerr);

    
    BOOST_CHECK_NO_THROW(stack.pop());
}

BOOST_AUTO_TEST_CASE(testPrint) {
    Stack<int> stack;
    stack.push(1);
    stack.push(2);
    
    std::ostringstream oss;
    std::streambuf* oldCout = std::cout.rdbuf(oss.rdbuf());

    stack.print();
    
    
    std::cout.rdbuf(oldCout);

    BOOST_CHECK_EQUAL(oss.str(), "2 1 \n");
}

BOOST_AUTO_TEST_SUITE_END()