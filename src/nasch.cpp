//
// Created by dl11 on 3/12/23.
//

#include "nasch.h"
#include "tracing.h"
#include <stdint.h>

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
  for (size_t i = 0; i < r.voitures.size(); ++i) {
    Voiture &voiture = r.voitures[i];
    if (i < r.voitures.size() - 1) {
      Voiture &voitureSuivante = r.voitures[i + 1];
      if (voitureSuivante.position - voiture.position >= voiture.vitesse) {
        voiture.vitesse++;
      } else {
        voiture.vitesse = voitureSuivante.position - voiture.position;
      }
    } else {
      voiture.vitesse++;
    }
  }
}

void freiner(Route &r) {

}

void ralentir(Route &r) {

}

void deplacer(Route &r) {

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

void supprimer(Route &r, char Id) {

}

void simuler(Route &r, int n) {

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

}

int saVitesse(const Route &r, char Id) {
  return 0;
}

bool aRalenti(const Route &r, char Id) {
  return false;
}

void setVMax(Route &r, int newVMax) {

}

void setPV(Route &r, double newPV) {

}

}