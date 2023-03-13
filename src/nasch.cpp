//
// Created by dl11 on 3/12/23.
//

#include "nasch.h"
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
  for (auto & voiture : r.voitures) {
    voiture.vitesse += 1;
  }
}

size_t voitureSuivante(const Route &r, size_t start) {
  size_t index = 0;
  size_t s = r.cellules.size();
  while (index < s) {
    if (not r.cellules.at((index + start) % s).estVide()) {
      return (index + start) % s;
    }
  }
}

void freiner(Route &r) {
  for (auto & voiture : r.voitures) {
    int dist = std::abs(r.voitures.at(voitureSuivante(r, voiture.position)).position - voiture.position);
    if (voiture.vitesse > dist) {
      voiture.vitesse = dist;
    } else {
      voiture.vitesse++;
    }
  }
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

Voiture * trouverSelonId(Route& r, unsigned char id) {
  for (Voiture& v : r.voitures) {
    if (v.id == id) {
      return &v;
    }
  }
  return nullptr;
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
  // TODO: Optimiser / Refactorings ce code.
  for (size_t i = position-1; i < r.cellules.size(); ++i) {
    if (r.cellules[i].estVide()) {
      unsigned char id = r.prochainId();
      if (id == 0) {
        tracing::trace("Impossible d'ajouter une voiture, la route est pleine.");
        return;
      }
      r.voitures.emplace_back(id, i, 0, false);
      r.cellules[i].voiture = &r.voitures.back();
      return;
    }
  }
  for (size_t i = 0; i < position; i++) {
    if (r.cellules[i].estVide()) {
      unsigned char id = r.prochainId();
      if (id == 0) {
        tracing::trace("Impossible d'ajouter une voiture, la route est pleine.");
        return;
      }
      r.voitures.emplace_back(id, i, 0, false);
      r.cellules[i].voiture = &r.voitures.back();
      return;
    }
  }
  tracing::trace("Impossible d'ajouter une voiture, la route est pleine.");
}

const Voiture * trouverSelonId(const Route& r, unsigned char id) {
  for (const Voiture& v : r.voitures) {
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
  r.voitures.erase(r.voitures.begin());

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
  char * buffer = (char *)calloc(sizeof(unsigned char), r.cellules.size());

  for (size_t i = 0; i < r.cellules.size(); i++) {
    if (i % 10 == 0 and i > 0) {
      std::cout << "|";
    } else if (i % 5 == 0 and i > 0) {
      std::cout << "+";
    } else {
      std::cout << ".";
    }
    *(buffer + i) = r.cellules.at(i).estVide() ? ' ' : r.cellules.at(i).voiture->id;
  }
  *(buffer + r.cellules.size() - 1) = '\0';
  std::cout << std::endl << buffer << std::endl;
  free(buffer);
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
  const Voiture * v = trouverSelonId(r, (unsigned char)Id);
  if (v == nullptr) {
    tracing::trace(&"Error: Impossible de trouver la voiture ayant l'id:" [ Id]);
    return -1;
  }
  return v->vitesse;
}

bool aRalenti(const Route &r, char Id) {
  const Voiture * v = trouverSelonId(r, (unsigned char)Id);
  if (v == nullptr) {
    tracing::trace(&"Error: Impossible de trouver la voiture ayant l'id:" [ Id]);
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