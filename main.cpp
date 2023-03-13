#include <iostream>
#include "src/nasch.h"
#include "src/tests.h"

using namespace std;

int main() {
  std::cout << "Hello, World!" << std::endl;
  testing::test1();
  testing::test1Bis();
  testing::test1Ter();

  NaSch::Route r;
  NaSch::initialiser(r, 50, 3);

  return 0;
}
