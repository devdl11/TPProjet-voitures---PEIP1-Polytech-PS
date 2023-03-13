//
// Created by dl11 on 3/12/23.
//

#include "nasch.h"
#include <stdint.h>
#include <iostream>
#include <cstdlib>
#include <vector>
#include "tracing.h"

namespace NaSch {

bool Route::idsValides() {
  uint8_t index = 0;
  for (auto &voiture : voitures) {
    idsBuffer[index++] = voiture.id;
  }
  for (uint8_t j = 0; j < index; ++j) {
    for (uint8_t k = j + 1; k < index; ++k) {
      if (idsBuffer[j] == idsBuffer[k]) {
        return false;
      }
    }
  }
  return true;
}
unsigned char Route::prochainId() {
  if (availableIds.empty()) {
    return 0;
  }
  unsigned char id = availableIds.back();
  availableIds.pop_back();
  return id;
}

void initialiser(Route &r, std::size_t taille, int vmax) {
  r = Route(vmax, 0.0, std::vector<Voiture>(taille), std::vector<Cellule>(taille));
}

void accelerer(Route &r) {

}

void freiner(Route &r) {

}

void ralentir(Route &r) {
  for (size_t i = 0; i < r.voitures.size(); i++)
  {
    double po = (rand()%100)/100;
    if (po > r.pv)
    {
      r.voitures.at(i).vitesse--;
    }
  }
}

void deplacer(Route &r) {
  for (size_t i = 0; i < r.voitures.size(); i++)
  {
    if (r.voitures.at(i).position == r.cellules.size())
    {
      r.voitures.at(i).position = 0;
    }
    else{
      r.voitures.at(i).position++;
    }
  }
}

void ajouter(Route &r, int position) {
  // On suppose que la position est valide.

}

Voiture * trouverSelonId(Route& r, unsigned char id) {
  for (Voiture& v : r.voitures) {
    if (v.id == id) {
      return &v;
    }
  }
  return nullptr;
}

void supprimer(Route &r, char Id) {
  Voiture *pt_vt = trouverSelonId(r,Id);
  if (pt_vt == nullptr)
  {
    tracing::trace(&"Error : Impossible de trouver la voiture ayant l'id : " [ Id]);
    return;
  }
  r.voitures.erase(r.voitures.begin() + (pt_vt->position));

}

void simuler(Route &r, int n) {
  for (int i = 0; i < n; i++)
  {
    accelerer(r);
    freiner(r);
    ralentir(r);
    deplacer(r);
  }
}

void afficherR(const NaSch::Route &r) {

}

void afficherV(const Route &r, char Id) {
  for (size_t i = 0; i < r.voitures.size(); i++)
  {
    if (r.voitures.at(i).id == Id)
    {
      std::cout << "La position de la voiture " << Id << " est : " << r.voitures.at(i).position << ", sa vitesse est de " << r.voitures.at(i).vitesse;
      if (r.voitures.at(i).freinage)
      {
        std::cout << " et elle a freiné à la dernière étape 3." << std::endl;
      }
      else{
        std::cout << " et elle n'a pas freiné à la dernière étape 3." << std::endl;
      }
    }
  }
}

int saVitesse(const Route &r, char Id) {
  return 0;
}

bool aRalenti(const Route &r, char Id) {
  return false;
}

void setVMax(Route &r, int newVMax) {
  r.vmax = newVMax;
}

void setPV(Route &r, double newPV) {
  r.pv = newPV;
}

}