//
// Created by dl11 on 3/12/23.
//

#ifndef MAINDIR_SRC_NASCH_H_
#define MAINDIR_SRC_NASCH_H_

#include <utility>
#include <vector>
#include <cstring>

namespace NaSch {

const int MAX_VOITURES = 52;
constexpr char ALPHABET[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

// Buffer pour les ids. Puisqu'on souhaite garder une taille fixe, on utilise un tableau statique initialisé à 0.
static unsigned char idsBuffer[MAX_VOITURES] = {0};

struct Voiture {
  const char id;
  int position;
  int vitesse;
  bool freinage;

  Voiture() : Voiture(0, 0, false) {}
  // Ici utiliser `ALPHABET[0]` est safe puisque la taille de `ALPHABET` est connue à la compilation et ne peut changer.
  Voiture(int position, int vitesse, bool freinage) : Voiture(ALPHABET[0], position, vitesse, freinage) {}
  Voiture(char id, int position, int vitesse, bool freinage)
      : id(id), position(position), vitesse(vitesse), freinage(freinage) {}

};

struct Cellule {
  Voiture *voiture;

  Cellule() : voiture(nullptr) {}

  bool estVide() const { return voiture == nullptr; }
};

struct Route {
  std::vector<unsigned char> availableIds;
  std::vector<Voiture> voitures;
  std::vector<Cellule> cellules;
  int vmax;
  double pv;

  Route() : Route(0, 0.0) {}
  Route(int vmax, double pv) : Route(vmax, pv, {}, {}) {}
  // strlen va être évaluée à la compilation et remplacée par la valeur de la taille de ALPHABET qui est constante à la compilation.
  Route(int vmax, double pv, std::vector<Voiture> voitures, std::vector<Cellule> cellules)
      : vmax(vmax), pv(pv), voitures(std::move(voitures)), cellules(std::move(cellules)), availableIds(ALPHABET, ALPHABET + std::strlen(ALPHABET)) {}

  bool idsValides();
  unsigned char prochainId();
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
