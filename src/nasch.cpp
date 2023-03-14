//
// Created by dl11 on 3/12/23.
//

#include "nasch.h"
#include <iostream>
#include <cstdlib>
#include <vector>
#include <set>
#include <random>
#include "tracing.h"

namespace NaSch {

bool Route::idsValides() {
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
  if (idsIndex < 0 or idsIndex >= ALPHABET_SIZE) {
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

void initialiser(Route &r, std::size_t taille, int vmax) {
  r = Route(vmax, 0.0, std::vector<Voiture>(taille));
}

void accelerer(Route &r) {
  for (size_t i = 0; i < r.numVoitures; i++) {
    if (r.voitures[i].id[0] == INVALID_ID or r.voitures[i].id == nullptr) {
      tracing::error("Voiture sans id valide");
      exit(1);
    }
    if (r.voitures[i].vitesse < r.vmax) {
      r.voitures[i].vitesse++;
    }
  }
}

const Voiture * voitureSuivante(const Route &r, size_t start) {
  Voiture *v = nullptr;
  for (auto iterator : r.voituresMap) {
    if (v == nullptr) {
      v = iterator.second;
    }
    if (iterator.first > start) {
      return iterator.second;
    }
  }
  return v;
}

void freiner(Route &r) {
  for (size_t i = 0; i < r.numVoitures; i++) {
    Voiture &voiture = r.voitures[i];
    const Voiture * v = voitureSuivante(r, voiture.position);
    if (v == nullptr) {
      tracing::error("Impossible de trouver la voiture !");
      continue;
    }
    int dist = v->position;
    if (dist < voiture.position) {
        dist += (int)r.voitures.size();
    }
    dist -= voiture.position;
    if (voiture.vitesse >= dist) {
      voiture.vitesse = dist - 1;
    }
  }
}

void ralentir(Route &r) {
  static std::random_device dev;
  static std::mt19937 rng(dev());
  std::uniform_real_distribution<> dist(0, 1);
  for (size_t i = 0; i < r.numVoitures; i++) {
    double po = dist(rng);
    if (po < r.pv and r.voitures.at(i).vitesse > 0) {
      r.voitures.at(i).vitesse--;
    }
  }
}

const Voiture *trouverSelonId(const Route &r, char id) {
  for (const Voiture &v : r.voitures) {
    if (v.id[0] == id) {
      return &v;
    }
  }
  return nullptr;
}

void deplacer(Route &r) {
  std::map<int, Voiture *> voituresMap;
  for (auto it : r.voituresMap) {
    it.second->position = (it.second->position + it.second->vitesse) % (int)r.voitures.size();
    voituresMap[it.second->position] = it.second;
  }
  r.voituresMap = std::move(voituresMap);
}

void ajouter(Route &r, int position) {
  // On suppose que la position est valide.
  if (r.numVoitures >= r.voitures.size()) {
    tracing::error("Impossible d'ajouter une voiture, la route est pleine.");
    return;
  }

  while (r.voituresMap.count(position % (int)r.voitures.size())) {
    position++;
  }

  Voiture v = Voiture(&r.prochainId(), position, 0, false);
  if (v.id[0] == INVALID_ID) {
    tracing::error("Impossible d'ajouter une voiture, la route est pleine. Mais comment sommes nous arrivés là ?");
    return;
  }
  r.voitures.at(r.numVoitures) = v;
  r.voituresMap[position] = &r.voitures.at(r.numVoitures);
  r.numVoitures++;
}

void supprimer(Route &r, char Id) {
  const Voiture *pt_vt = trouverSelonId(r, Id);
  if (pt_vt == nullptr) {
    tracing::trace(&"Error : Impossible de trouver la voiture ayant l'id : "[Id]);
    return;
  }
  // This will crash if in somehow the the map is not in sync with the vector.
  r.voituresMap.erase(pt_vt->position);
  int fromWhereLinea = pt_vt->id[0] - ALPHABET[0];
  // Here we need to move all the cars after the one we deleted, setting their id accordingly and updating the map
  // cause the pointer will be invalid.
  for (size_t i = fromWhereLinea; i < r.numVoitures - 1; i++) {
    r.voitures.at(i) = r.voitures.at(i + 1);
    r.voitures.at(i).id--;
    r.voituresMap[r.voitures.at(i).position] = &r.voitures.at(i);
  }
  r.numVoitures--;
  r.idsIndex--;
  // We don't need to do anything with the last car, it will be overwritten when we add a new one.
}

void simuler(Route &r, int n) {
  for (int vi = 0; vi < r.numVoitures; vi++) {
    r.voitures.at(vi).freinage = false;
  }
  for (int i = 0; i < n; i++) {
    accelerer(r);
    freiner(r);
    ralentir(r);
    deplacer(r);
  }
}

void afficherR(const NaSch::Route &r) {
  char *buffer = (char *) calloc(sizeof(char), r.voitures.size() + 1);

  for (size_t i = 1; i < r.voitures.size() + 1; i++) {
    if (i % 10 == 0 and i > 0) {
      std::cout << "|";
    } else if (i % 5 == 0 and i > 0) {
      std::cout << "+";
    } else {
      std::cout << ".";
    }
    *(buffer + i - 1) = r.voituresMap.count((int)i - 1) == 0 ? ' ' : r.voituresMap.at((int)i - 1)->id[0];
  }
  *(buffer + r.voitures.size()) = '\0';
  std::cout << std::endl << buffer << std::endl;
  free(buffer);
}

void afficherV(const Route &r, char Id) {
  const Voiture *v = trouverSelonId(r, Id);
  if (v == nullptr) {
      tracing::error(&"Impossible de trouver la voiture ayant l'id : "[Id]);
      return;
  }
  std::cout << "La position de la voiture " << Id << " est : " << v->position
            << ", sa vitesse est de " << v->vitesse;
  if (v->freinage) {
    std::cout << " et elle a freiné à la dernière étape 3." << std::endl;
  } else {
    std::cout << " et elle n'a pas freiné à la dernière étape 3." << std::endl;
  }
}

int saVitesse(const Route &r, char Id) {
  const Voiture *v = trouverSelonId(r, Id);
  if (v == nullptr) {
    tracing::error(&"Impossible de trouver la voiture ayant l'id:"[Id]);
    return -1;
  }
  return v->vitesse;
}

bool aRalenti(const Route &r, char Id) {
  const Voiture *v = trouverSelonId(r,  Id);
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