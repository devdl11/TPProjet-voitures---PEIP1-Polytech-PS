//
// Created by dl11 on 3/12/23.
//

#ifndef MAINDIR_SRC_NASCH_H_
#define MAINDIR_SRC_NASCH_H_

#include <utility>
#include <vector>
#include <cstring>
#include <map>

// real size = size + 1 for the null terminator
#define ALPHABET_SIZE 53

namespace NaSch {

constexpr static const char ALPHABET[ALPHABET_SIZE] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
constexpr static const char INVALID_ID = -1;

// Buffer pour les ids. Puisqu'on souhaite garder une taille fixe, on utilise un tableau statique initialisé à 0.
static unsigned char idsBuffer[ALPHABET_SIZE] = {0};

struct Voiture {
  const char * id;
  int position;
  int vitesse;
  bool freinage;

  Voiture() : Voiture(0, 0, false) {}
  // Ici utiliser `ALPHABET[0]` est safe puisque la taille de `ALPHABET` est connue à la compilation et ne peut changer.
  Voiture(int position, int vitesse, bool freinage) : Voiture(&INVALID_ID, position, vitesse, freinage) {}
  Voiture(const char * id, int position, int vitesse, bool freinage)
      : id(id), position(position), vitesse(vitesse), freinage(freinage) {}

};

struct Route {
  // Don't edit the position field of the Voiture struct, cause it's synchronized with the key of the map !
  // or else, call synchroniserVoitures();
  // Don't edit the number of elements in the vector, cause it's synchronized with the numVoitures field !
  std::vector<Voiture> voitures;
  std::map<int, Voiture *> voituresMap;

  int vmax;
  double pv;

  // Don't edit theses fields, they are used to generate ids and keep track of the number of cars.
  // TODO maybe do: Merge some of the functions inside the struct and make theses fields private.
  size_t idsIndex = 0;
  size_t numVoitures = 0;

  Route() : Route(0, 0.0) {}
  Route(int vmax, double pv) : Route(vmax, pv, {}) {}
  // strlen va être évaluée à la compilation et remplacée par la valeur de la taille de ALPHABET qui est constante à la compilation.
  Route(int vmax, double pv, std::vector<Voiture> voitures)
      : vmax(vmax), pv(pv), voitures(std::move(voitures)) {}

  bool idsValides();
  const char & prochainId();
  void synchroniserVoitures();
};

// Fonctions fournies
void initialiser(Route &r, std::size_t taille, int vmax);

void accelerer(Route &r);
void freiner(Route &r);
void ralentir(Route &r);

void deplacer(Route &r);

void ajouter(Route &r, int position);
void supprimer(Route &r, char Id);
void simuler(Route &r, int n);

void afficherR(Route const &r);
void afficherV(Route const &r, char Id);

int saVitesse(Route const &r, char Id);
bool aRalenti(Route const &r, char Id);
void setVMax(Route &r, int newVMax);
void setPV(Route &r, double newPV);

}

#endif //MAINDIR_SRC_NASCH_H_
