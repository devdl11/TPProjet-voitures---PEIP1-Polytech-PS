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

struct Voiture {
  Voiture() : Voiture(0, 0, false) {}
  Voiture(int position, int vitesse, bool freinage) : Voiture(&INVALID_ID, position, vitesse, freinage) {}
  Voiture(const char *id, int position, int vitesse, bool freinage)
      : id(id), position(position), vitesse(vitesse), freinage(freinage) {}

  [[nodiscard]]
  int getPosition() const {
    return position;
  }

  const char *id;
  int vitesse;
  bool freinage;

 private:
  int position;
  // On autorise l'accès à la position uniquement à la struct Route.
  friend struct Route;
};

struct Route {
  Route() : Route(0, 0.0) {}
  Route(int vmax, double pv) : Route(vmax, pv, {}) {}
  Route(int vmax, double pv, std::vector<Voiture> voitures) : vmax(vmax), pv(pv), voitures(std::move(voitures)) {}

  // custom
  [[maybe_unused]]
  bool idsValides();
  [[maybe_unused]]
  void synchroniserVoitures();
  const Voiture *voitureSuivante(size_t position);
  // regular
  void accelerer();

  void freiner();
  void deplacer();
  void ralentir();
  void ajouter(int position, int vitesse, bool freinage);

  void supprimerSelonId(const char *id);
  const Voiture *voitureSelonId(const char *id) const;

  void simuler(int iterations);

  void afficher() const;

 private:
  const char &prochainId();

 public:
  std::vector<Voiture> voitures;
  int vmax;
  double pv;

 private:
  std::map<int, Voiture *> voituresMap;
  size_t idsIndex = 0;
  size_t numVoitures = 0;
};

}

#endif //MAINDIR_SRC_NASCH_H_
