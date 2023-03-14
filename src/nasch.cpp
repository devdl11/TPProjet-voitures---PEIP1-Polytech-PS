//
// Created by dl11 on 3/12/23.
//

#include "nasch.h"
#include <iostream>
#include <cstdlib>
#include <set>
#include <random>
#include <algorithm>
#include "tracing.h"

namespace NaSch {

[[maybe_unused]] bool Route::idsValides() {
  std::set<char> ids = std::set<char>();
  for (size_t i = 0; i < numVoitures; ++i) {
    if (voitures[i].id[0] == INVALID_ID) {
      tracing::error("Voiture sans id valide");
      exit(1);
    }
    ids.insert(voitures[i].id[0]);
  }
  return ids.size() == numVoitures;
}

const char &Route::prochainId() {
  if (idsIndex >= ALPHABET_SIZE) {
    return INVALID_ID;
  }
  return ALPHABET[idsIndex++];
}

[[deprecated("synchroniserVoitures() is deprecated cause the map is normally updated automatically.")]]
void Route::synchroniserVoitures() {
  tracing::warning("Appel d'une fonction à risque: synchroniserVoitures");
  voituresMap.clear();
  for (size_t i = 0; i < numVoitures; ++i) {
    if (voituresMap.count(voitures[i].position) > 0) {
      tracing::error("Plusieurs voitures ont la même position");
      exit(1);
    }
    voituresMap[voitures[i].position] = &voitures[i];
  }
}

void Route::accelerer() {
  for (size_t i = 0; i < numVoitures; i++) {
    if (voitures[i].id == nullptr or voitures[i].id[0] == INVALID_ID) {
      tracing::error("Voiture sans id valide");
      exit(1);
    }
    if (voitures[i].vitesse < vmax) {
      voitures[i].vitesse++;
    }
  }
}

void Route::freiner() {
  for (size_t i = 0; i < numVoitures; i++) {
    Voiture &voiture = voitures[i];
    const Voiture *v = voitureSuivante(voiture.position);
    if (v == nullptr) {
      tracing::error("Impossible de trouver la voiture !");
      continue;
    }
    int dist = v->position;
    if (dist < voiture.position) {
      dist += (int) voitures.size();
    }
    dist -= voiture.position;
    if (voiture.vitesse >= dist) {
      voiture.vitesse = dist - 1;
    }
  }
}

const Voiture *Route::voitureSuivante(size_t position) {
  Voiture *v = nullptr;
  for (auto iterator : voituresMap) {
    if (v == nullptr) {
      v = iterator.second;
    }
    if (iterator.first > position) {
      return iterator.second;
    }
  }
  return v;
}

void Route::deplacer() {
  std::map<int, Voiture *> newVoituresMap;
  for (auto it : voituresMap) {
    it.second->position = (it.second->position + it.second->vitesse) % (int)voitures.size();
    newVoituresMap[it.second->position] = it.second;
  }
  voituresMap = std::move(newVoituresMap);
}

void Route::ralentir() {
  static std::random_device dev;
  static std::mt19937 rng(dev());
  std::uniform_real_distribution<> dist(0, 1);
  for (size_t i = 0; i < numVoitures; i++) {
    double po = dist(rng);
    if (po < pv and voitures.at(i).vitesse > 0) {
      voitures.at(i).vitesse--;
    }
  }

}

const Voiture *Route::voitureSelonId(const char *id) const {
  auto search = std::find_if(voitures.begin(), voitures.end(), [id](const Voiture &v) { return v.id[0] == *id; });
  return search == voitures.end() ? nullptr : &(*search);
}

void Route::ajouter(int position, int vitesse, bool freinage) {
  // On suppose que la position est valide.
  if (numVoitures >= voitures.size()) {
    tracing::error("Impossible d'ajouter une voiture, la route est pleine.");
    return;
  }

  while (voituresMap.count(position % (int)voitures.size())) {
    position++;
  }

  Voiture v = Voiture(&prochainId(), position, vitesse, freinage);
  if (v.id[0] == INVALID_ID) {
    tracing::error("Impossible d'ajouter une voiture, la route est pleine. Mais comment sommes nous arrivés là ?");
    return;
  }
  voitures.at(numVoitures) = v;
  voituresMap[position] = &voitures.at(numVoitures);
  numVoitures++;

}

void Route::supprimerSelonId(const char *id) {
  const Voiture *pt_vt = voitureSelonId(id);
  if (pt_vt == nullptr) {
    tracing::warning("Error : Impossible de trouver la voiture ayant l'id ");
    tracing::warning(id);
    return;
  }
  // This will crash if in somehow the the map is not in sync with the vector.
  voituresMap.erase(pt_vt->position);
  int fromWhereLinea = pt_vt->id[0] - ALPHABET[0];
  // Here we need to move all the cars after the one we deleted, setting their id accordingly and updating the map
  // cause the pointer will be invalid.
  for (size_t i = fromWhereLinea; i < numVoitures - 1; i++) {
    voitures.at(i) = voitures.at(i + 1);
    voitures.at(i).id--;
    voituresMap[voitures.at(i).position] = &voitures.at(i);
  }
  numVoitures--;
  idsIndex--;
  // We don't need to do anything with the last car, it will be overwritten when we add a new one.
}

void Route::simuler(int iterations) {
  for (int vi = 0; vi < numVoitures; vi++) {
    voitures.at(vi).freinage = false;
  }
  for (int i = 0; i < iterations; i++) {
    accelerer();
    freiner();
    ralentir();
    deplacer();
  }
}

void Route::afficher() const {
  char *buffer = static_cast<char *>(calloc(sizeof(char), voitures.size() + 1));

  if (buffer == nullptr) {
    tracing::error("Impossible d'allouer de la mémoire pour l'affichage");
    exit(1);
  }

  for (size_t i = 1; i < voitures.size() + 1; i++) {
    if (i % 10 == 0 and i > 0) {
      std::cout << "|";
    } else if (i % 5 == 0 and i > 0) {
      std::cout << "+";
    } else {
      std::cout << ".";
    }
    *(buffer + i - 1) = voituresMap.count((int)i - 1) == 0 ? ' ' : voituresMap.at((int)i - 1)->id[0];
  }
  *(buffer + voitures.size()) = '\0';
  std::cout << std::endl << buffer << std::endl;
  free(buffer);
}

}