//
// Created by dl11 on 3/14/23.
//

#ifndef MAINDIR_SRC_NASCH_TEST_H_
#define MAINDIR_SRC_NASCH_TEST_H_

#include "nasch.h"

namespace testing {

void initialiser(NaSch::Route &r, std::size_t taille, int vmax);

void accelerer(NaSch::Route &r);
void freiner(NaSch::Route &r);
void ralentir(NaSch::Route &r);

void deplacer(NaSch::Route &r);

void ajouter(NaSch::Route &r, int position);
void supprimer(NaSch::Route &r, char Id);
void simuler(NaSch::Route &r, int n);

void afficherR(NaSch::Route const &r);
void afficherV(NaSch::Route const &r, char Id);

int saVitesse(NaSch::Route const &r, char Id);
bool aRalenti(NaSch::Route const &r, char Id);
void setVMax(NaSch::Route &r, int newVMax);
void setPV(NaSch::Route &r, double newPV);


}

#endif //MAINDIR_SRC_NASCH_TEST_H_
