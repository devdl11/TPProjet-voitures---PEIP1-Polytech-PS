#include <iostream>
#include "tests/tests.h"

#define TEST true

using namespace std;

#if TEST
void test() {
  cout << "Default tests..." << endl;
  testing::test1();
  testing::test1Bis();
  testing::test1Ter();

  testing::testFramework.loadTestFiles("./unitTests");
  testing::testFramework.runTests();

}
#else
void test() {}
#endif

int main() {
  test();
  return 0;
}
