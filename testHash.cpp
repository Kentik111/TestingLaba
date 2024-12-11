#define BOOST_TEST_MODULE HashTest
#include <boost/test/included/unit_test.hpp>
#include "../structs/hash.h"

BOOST_AUTO_TEST_SUITE(HashTableTests)

BOOST_AUTO_TEST_CASE(TestInsertAndGet) {
    HashTable<std::string, int> hashTable(10);
    
    hashTable.insert("one", 1);
    hashTable.insert("two", 2);
    
    BOOST_CHECK_EQUAL(hashTable.get("one"), 1);
    BOOST_CHECK_EQUAL(hashTable.get("two"), 2);
}

BOOST_AUTO_TEST_CASE(TestGetNonExistentKey) {
    HashTable<std::string, int> hashTable(10);
    
    hashTable.insert("one", 1);
    
    BOOST_CHECK_THROW(hashTable.get("two"), std::out_of_range);
}

BOOST_AUTO_TEST_CASE(TestRemove) {
    HashTable<std::string, int> hashTable(10);
    
    hashTable.insert("one", 1);
    hashTable.insert("two", 2);
    
    hashTable.remove("one");
    
    BOOST_CHECK_THROW(hashTable.get("one"), std::out_of_range);
    BOOST_CHECK_EQUAL(hashTable.get("two"), 2);
}

BOOST_AUTO_TEST_CASE(TestContains) {
    HashTable<std::string, int> hashTable(10);
    
    hashTable.insert("one", 1);
    
    BOOST_CHECK(hashTable.contains("one"));
    BOOST_CHECK(!hashTable.contains("two"));
    
    hashTable.remove("one");
    
    BOOST_CHECK(!hashTable.contains("one"));
}

BOOST_AUTO_TEST_CASE(TestMultipleCollisions) {
    HashTable<int, std::string> hashTable(5); 
    
    hashTable.insert(1, "one");
    hashTable.insert(6, "six"); 
    
    BOOST_CHECK_EQUAL(hashTable.get(1), "one");
    BOOST_CHECK_EQUAL(hashTable.get(6), "six");
}

BOOST_AUTO_TEST_CASE(TestSize) {
    HashTable<std::string, int> hashTable(10);
    
    BOOST_CHECK_EQUAL(hashTable.getSize(), 10);
    
    hashTable.insert("one", 1);
    
    BOOST_CHECK_EQUAL(hashTable.getSize(), 10); // Размер не изменяется при добавлении
}

BOOST_AUTO_TEST_CASE(TestPrint) {
    HashTable<std::string, int> hashTable(10);
    
    hashTable.insert("one", 1);
    hashTable.insert("two", 2);

    BOOST_CHECK_NO_THROW(hashTable.print());
}

BOOST_AUTO_TEST_SUITE_END()