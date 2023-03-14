#include <iostream>
#include "src/nasch_test.h"
#include "src/tests.h"

using namespace std;

int main() {
  testing::test1();
  testing::test1Bis();
  testing::test1Ter();

  NaSch::Route r;
  testing::initialiser(r, 50, 3);
  testing::ajouter(r, 5);
  testing::ajouter(r, 5);
  testing::ajouter(r, 5);
  testing::ajouter(r, 5);
  testing::afficherR(r);
  testing::supprimer(r, 'B');
  testing::afficherR(r);
  testing::ajouter(r, 5);
  testing::afficherR(r);
  return 0;
}
