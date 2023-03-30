#include <iostream>
#include "tests/tests.h"
#include "src/tracing.h"

#define TEST true

using namespace std;

void resetRand() {
  srand(DEBUG ? time(nullptr) : 1);
}

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
