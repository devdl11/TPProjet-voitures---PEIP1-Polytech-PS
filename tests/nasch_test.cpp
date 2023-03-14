//
// Created by dl11 on 3/14/23.
//
#include "nasch_test.h"
#include <iostream>
#include <vector>
#include <set>
#include "../src/tracing.h"

using namespace NaSch;

namespace testing {

void initialiser(Route &r, std::size_t taille, int vmax) {
  if (taille >= ALPHABET_SIZE) {
    tracing::warning("La taille de la route est trop grande ! Elle est limitée à ");
    tracing::warning(std::to_string(ALPHABET_SIZE).c_str());
  }
  r = Route(vmax, 0, std::vector<Voiture>(taille, Voiture()));
}

void accelerer(Route &r) {
  r.accelerer();
}

void freiner(Route &r) {
  r.freiner();
}

void ralentir(Route &r) {
  r.ralentir();
}

void deplacer(Route &r) {
  r.deplacer();
}

void ajouter(Route &r, int position) {
  r.ajouter(position, 0, false);
}

void supprimer(Route &r, char Id) {
  r.supprimerSelonId(&Id);
}

void simuler(Route &r, int n) {
  r.simuler(n);
}

void afficherR(const Route &r) {
  r.afficher();
}

void afficherV(const Route &r, char Id) {
  const Voiture *v = r.voitureSelonId(&Id);
  if (v == nullptr) {
    tracing::error(&"Impossible de trouver la voiture ayant l'id : "[Id]);
    return;
  }
  std::cout << "La position de la voiture " << Id << " est : " << v->getPosition()
            << ", sa vitesse est de " << v->vitesse;
  if (v->freinage) {
    std::cout << " et elle a freiné à la dernière étape 3." << std::endl;
  } else {
    std::cout << " et elle n'a pas freiné à la dernière étape 3." << std::endl;
  }
}

int saVitesse(const Route &r, char Id) {
  const Voiture *v = r.voitureSelonId(&Id);
  if (v == nullptr) {
    tracing::error(&"Impossible de trouver la voiture ayant l'id:"[Id]);
    return -1;
  }
  return v->vitesse;
}

bool aRalenti(const Route &r, char Id) {
  const Voiture *v = r.voitureSelonId(&Id);
  if (v == nullptr) {
    tracing::error(&"Impossible de trouver la voiture ayant l'id:"[Id]);
    return false;
  }
  return v->freinage;
}

void setVMax(Route &r, int newVMax) {
  r.vmax = newVMax;
}

void setPV(Route &r, double newPV) {
  r.pv = newPV;
}

}
