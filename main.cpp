#include <iostream>
#include "src/nasch.h"
#include "src/tests.h"

using namespace std;

int main() {
  testing::test1();
  testing::test1Bis();
  testing::test1Ter();

  NaSch::Route r;
  NaSch::initialiser(r, 50, 3);
  NaSch::ajouter(r, 5);
  NaSch::ajouter(r, 5);
  NaSch::ajouter(r, 5);
  NaSch::ajouter(r, 5);
  NaSch::afficherR(r);
  return 0;
}
