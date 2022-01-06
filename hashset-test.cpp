#include <cs70/stringhash.hpp>  // Declares myHash(const std::string& str)

size_t myhash(int s) {
    return 0;
}


#include "hashset.hpp"
#include <cs70/testinglogger.hpp>

using namespace std;



/** \brief Tests the constructor, insert and size functionality
 */
bool constructorInsertTest() {
    TestingLogger log("Constructor");

    HashSet<int> newTable1;
    // creates a new table and tests to make sure size is 0
    affirm(newTable1.size() == 0);
    newTable1.insert(1);
    affirm(newTable1.size() == 1);
    // adds a 1 and tests if the size increases accordingly

    HashSet<string> newTable2;
    // creates a new string table
    affirm(newTable2.size() == 0);
    newTable2.insert("a");
    affirm(newTable2.size() == 1);
    // test to affitm size doesnt change when inserting the same value
    newTable2.insert("a");
    affirm(newTable2.size() == 1);


    return log.summarize();
}
/** \brief Tests the exists function, insert and size functionality
 */
bool existsTest() {
    TestingLogger log("Exists");

    HashSet<int> newTable1;
    // creates a new table
    affirm(newTable1.size() == 0);
    affirm(!newTable1.exists(1));
    // nothing inserted, make sure a value doesnt already exist
    newTable1.insert(1);
    affirm(newTable1.exists(1));
    // check if an inserted value exists

    HashSet<string> newTable2;
    affirm(newTable2.size() == 0);
    newTable2.insert("a");
    affirm(newTable2.exists("a"));
    // check if an inserted value exists for string table

    return log.summarize();
}
/** \brief Tests the paramaterized constructor, insert, buckets and size functionality
 */
bool paramConstructorTest() {
    TestingLogger log("Parameterized Constructor");

    HashSet<int> newTable1(50);
    // create a new int table using parameterized constructor
    affirm(newTable1.size() == 0);
    affirm(newTable1.buckets() == 50);
    // check to make sure there are 50 buckets but size is 0

    HashSet<string> newTable2(30);
    // create new string table
    affirm(newTable2.size() == 0);
    affirm(newTable2.buckets() == 30);
    // check to make sure there are 30 buckets but size is 0

    return log.summarize();
}
/** \brief Tests the reallocation function and buckets functionality
 */
bool reallocationTest() {
    TestingLogger log("Reallocation");

    size_t numBuckets = 1;
    size_t numReallocations = 0;
    HashSet<int> newTable1(1);
    affirm(newTable1.reallocations() == 0);

    for (size_t i = 0; i < 100; ++i) {
        newTable1.insert(i);
        if (newTable1.buckets() != numBuckets) {
            ++numReallocations;
            numBuckets = newTable1.buckets();
        }
    }
    affirm(newTable1.reallocations() == numReallocations);

    return log.summarize();
}
/** \brief Tests the collisions function and insert functionality
 */
bool collisionTest() {
    TestingLogger log("Collision");

    HashSet<int> newTable(50);
    affirm(newTable.collisions() == 0);

    newTable.insert(1);
    newTable.insert(2);
    affirm(newTable.collisions() == 1);
    newTable.insert(3);
    affirm(newTable.collisions() == 2);

    HashSet<int> newTable1(50);
    newTable1.insert(1);
    newTable1.insert(2);
    newTable1.insert(3);
    affirm(newTable1.collisions() == 2);

    return log.summarize();
}


int main() {
    TestingLogger alltests("All tests");

  // Print a summary of the all the affirmations and exit the program.
    constructorInsertTest();
    existsTest();
    paramConstructorTest();
    reallocationTest();
    collisionTest();

    if (alltests.summarize(true)) {
    return 0;  // Error code of 0 == Success!
    } else {
    return 2;  // Arbitrarily chosen exit code of 2 means tests failed.
    }
}
