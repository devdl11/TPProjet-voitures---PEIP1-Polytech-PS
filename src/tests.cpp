//
// Created by dl11 on 3/12/23.
//

#include "tests.h"
#include "nasch.h"

#include <iostream>

using namespace NaSch;

using std::cout, std::endl;

namespace testing {

void test1() {
  Route r;
  cout << "\nLancement de test1\n";
  initialiser(r, 50, 3);
  ajouter(r, 0); ajouter(r, 29); ajouter(r, 44);
  afficherR(r);
  /* a la premiere etape, l'avance sera de 1 unite, de 2 a la deuxieme et
   * de 3 a toutes les suivantes puisqu'il n'y a pas de probleme de distance
   * de securite.
   */
  simuler(r, 1);  afficherR(r);
  simuler(r, 1);  afficherR(r);
  simuler(r, 1);  afficherR(r);
  simuler(r, 15);
  afficherR(r);
  /*
  // Apres 18 unites de temps, chaque voiture doit avoir avancer de
  // 1 + 2 + 3 + 15*3 = 51 unites. A l'arrivee les voitures doivent donc
  // etre UNE position a droite de leur position de depart, avec une vitesse
  // maximale.
  */
  cout << "Fin de test1\n";
}

void test1Bis() {
  Route r;
  cout << "\n\nLancement de test1Bis\n";
  // On cree une route plus petite
  initialiser(r, 10, 3);
  afficherR(r);
  cout << "Ajout des voitures \n";
  ajouter(r, 7); ajouter(r, 0);
  afficherR(r);
  // avancerait normalement d'une cellule, puis deux, puis trois, puis trois
  // mais il n'y a que deux cases d'ecart entre les deux voitures.
  // A la troisieme acceleration la voiture A atteint une vitesse de 3 a la
  // 1ere etape mais doit freiner a cause de la distance de securite (deux
  // cellules libres avant B). Donc après cette étape A a avance de deux
  // cellules et B de 3.
  simuler(r, 3);
  afficherR(r);
  simuler(r, 12);
  // B s'est eloignee et a sa vitesse maximale. A peut accelerer une fois avant
  // d'atteindre sa vitesse maximale. Apres cela il n'y a plus ni acceleration
  // ni freinage.
  afficherR(r);
  cout << "Fin de test1Bis\n";
}

/* meme principe initial que test1Bis mais à l'ajout des voitures on laisse un
 * ecart de trois cellules entre les deux voitures. Il n'y a plus de freinage de
 * securite de A et on a 3 accelerations successives.
 * Pour epicer la simulation, après un certain nombre de pas de simulation
 * on ajoute une nouvelle voiture qui va changer la donne
 */
void test1Ter() {
  Route r;
  cout << "\n\nLancement de test1Ter\n";
  initialiser(r, 40, 3);
  afficherR(r);
  ajouter(r, 7); ajouter(r, 1);
  cout << "Ajout des voitures \n";
  afficherR(r);
  simuler(r, 11);
  afficherR(r);
  // une voiture s'incruste devant A.
  cout << "On ajoute la voiture C en derniere position" << endl;
  ajouter(r, 39);
  // A a ralenti, B va devoir ralentir, puis A et B vont progressivement
  // reacceler tandis que C poursuit sa route
  for(int i=0; i < 10; i += 1) {
    afficherR(r);
    // fragment de code a decommenter quand vous aurez ecrit la
    // fonction saVitesse()

    cout << "Vitesses: A = " << saVitesse(r, 'A')
         << " B = : " << saVitesse(r, 'B')
         << " C = " << saVitesse(r, 'C')
         << endl << endl;

    simuler(r, 1);
  }
  afficherR(r);
  cout << "\n\nAjout de D juste devant C" << endl;
  ajouter(r, 27);
  afficherR(r);
  for(int i = 0; i < 10; i++) { simuler(r, 1); afficherR(r); }
  cout << "Fin de test1Ter\n";
}

} // testing