//
// Created by dl11 on 3/12/23.
//

#include "tests.h"
#include "nasch_test.h"

#include <iostream>
#include <filesystem>
#include <fstream>

using namespace NaSch;

using std::cout, std::endl;
namespace fs = std::filesystem;

namespace testing {

void test1() {
  Route r;
  cout << "\nLancement de test1\n";
  initialiser(r, 50, 3);
  ajouter(r, 0);
  ajouter(r, 29);
  ajouter(r, 44);
  afficherR(r);
  /* a la premiere etape, l'avance sera de 1 unite, de 2 a la deuxieme et
   * de 3 a toutes les suivantes puisqu'il n'y a pas de probleme de distance
   * de securite.
   */
  simuler(r, 1);
  afficherR(r);
  simuler(r, 1);
  afficherR(r);
  simuler(r, 1);
  afficherR(r);
  simuler(r, 15);
  afficherR(r);
  /*
  // Apres 18 unites de temps, chaque voiture doit avoir avancer de
  // 1 + 2 + 3 + 15*3 = 51 unites. A l'arrivee les voitures doivent donc
  // etre UNE position a droite de leur position de depart, avec une vitesse
  // maximale.
  */
  cout << "Fin de test1\n";
}

void test1Bis() {
  Route r;
  cout << "\n\nLancement de test1Bis\n";
  // On cree une route plus petite
  initialiser(r, 10, 3);
  afficherR(r);
  cout << "Ajout des voitures \n";
  ajouter(r, 7);
  ajouter(r, 0);
  afficherR(r);
  // avancerait normalement d'une cellule, puis deux, puis trois, puis trois
  // mais il n'y a que deux cases d'ecart entre les deux voitures.
  // A la troisieme acceleration la voiture A atteint une vitesse de 3 a la
  // 1ere etape mais doit freiner a cause de la distance de securite (deux
  // cellules libres avant B). Donc après cette étape A a avance de deux
  // cellules et B de 3.
  simuler(r, 3);
  afficherR(r);
  simuler(r, 12);
  // B s'est eloignee et a sa vitesse maximale. A peut accelerer une fois avant
  // d'atteindre sa vitesse maximale. Apres cela il n'y a plus ni acceleration
  // ni freinage.
  afficherR(r);
  cout << "Fin de test1Bis\n";
}

/* meme principe initial que test1Bis mais à l'ajout des voitures on laisse un
 * ecart de trois cellules entre les deux voitures. Il n'y a plus de freinage de
 * securite de A et on a 3 accelerations successives.
 * Pour epicer la simulation, après un certain nombre de pas de simulation
 * on ajoute une nouvelle voiture qui va changer la donne
 */
void test1Ter() {
  Route r;
  cout << "\n\nLancement de test1Ter\n";
  initialiser(r, 40, 3);
  afficherR(r);
  ajouter(r, 7);
  ajouter(r, 1);
  cout << "Ajout des voitures \n";
  afficherR(r);
  simuler(r, 11);
  afficherR(r);
  // une voiture s'incruste devant A.
  cout << "On ajoute la voiture C en derniere position" << endl;
  ajouter(r, 39);
  // A a ralenti, B va devoir ralentir, puis A et B vont progressivement
  // reacceler tandis que C poursuit sa route
  for (int i = 0; i < 10; i += 1) {
    afficherR(r);
    // fragment de code a decommenter quand vous aurez ecrit la
    // fonction saVitesse()

    cout << "Vitesses: A = " << saVitesse(r, 'A')
         << " B = : " << saVitesse(r, 'B')
         << " C = " << saVitesse(r, 'C')
         << endl << endl;

    simuler(r, 1);
  }
  afficherR(r);
  cout << "\n\nAjout de D juste devant C" << endl;
  ajouter(r, 27);
  afficherR(r);
  for (int i = 0; i < 10; i++) {
    simuler(r, 1);
    afficherR(r);
  }
  cout << "Fin de test1Ter\n";
}

void TestFramework::loadTestFiles(const std::string &pa) {
  const fs::path path(pa);
  std::error_code er;
  if (fs::is_directory(path, er)) {
    for (const auto &entry : fs::directory_iterator(path)) {
      if (entry.is_regular_file() && entry.path().extension() == ".in") {
        filesPaths.push_back(std::move(entry.path().string()));
      }
    }
  } else {
    cout << "Error: " << er.message() << endl;
  }
}

void TestFramework::runTests() {
  for (const auto &path : filesPaths) {
    runTest(path);
  }
}

void trim(std::string *str) {
  // remove end of line
  str->erase((int)str->find_last_not_of('\n') + 1 + str->begin(), str->end());
  str->erase((int)str->find_last_not_of(' ') + 1 + str->begin(), str->end());
}

void TestFramework::runTest(const std::string &path) {
  const fs::path outputPath = path.substr(0, path.size() - 3) + ".out";
  // check if output file exists
  if (not fs::is_regular_file(outputPath)) {
    cout << "Error: output file " << outputPath << " does not exist" << endl;
    return;
  }
  const fs::path inputPath(path);
  std::fstream inputFile;
  std::fstream outputFile;
  inputFile.open(inputPath, std::ios::in);
  outputFile.open(outputPath, std::ios::in);
  if (not inputFile.is_open() or not outputFile.is_open()) {
    cout << "Error: could not open input file " << inputPath << " or output file "
         << outputPath << endl;
    inputFile.close();
    outputFile.close();
    return;
  }
  TestEnvironment env;
  bool hadError = false;
  cout << "Running test " << path.substr(0, path.size() - 3) << "..." << endl << endl;
  while (not inputFile.eof()) {
    debugOutput = "";
    std::string line;
    std::getline(inputFile, line);
    if (line.empty()) {
      continue;
    }
    if (line.at(0) == '~') {
      cout << line.substr(1) << endl;
      continue;
    }
    std::string result = env.runLine(line);
    if (result.empty()) {
      continue;
    }
    // split result into lines
    std::vector<std::string> lines;
    size_t start = 0;
    size_t pos;
    while ((pos = result.find('\n', start)) != std::string::npos) {
      lines.push_back(std::move(result.substr(start, pos)));
      trim(&lines.back());
      start = pos + 1;
    }
    lines.push_back(result.substr(start));
    bool didPrint = false;
    bool didMatch = true;
    // compare with output file
    for (const auto &li : lines) {
      if (outputFile.eof()) {
        cout << "Error: got '" << li << "' but there is nothing to compare with !" << endl;
        didPrint = true;
        hadError = true;
        break;
      }
      std::string outputLine;
      std::getline(outputFile, outputLine);
      if (li != outputLine) {
        cout << "Error: expected '" << outputLine << "' but got '" << li << "'" << endl;
        didPrint = true;
        didMatch = false;
        hadError = true;
      }
    }
    if (not didPrint and not didMatch) {
      cout << result << endl;
    }
  }
  if (not hadError) {
    cout << "Test passed" << endl;
  } else {
    cout << "Test failed" << endl;
  }
  inputFile.close();
  outputFile.close();
  cout << "=====================" << endl;
}

std::string TestEnvironment::runLine(const std::string &line) {
  std::vector<std::string> tokens;
  size_t start = 0;
  size_t pos;
  while ((pos = line.find(' ', start)) != std::string::npos) {
    tokens.push_back(line.substr(start, pos));
    start = pos + 1;
  }
  tokens.push_back(line.substr(start));
  if (tokens.empty()) {
    return "";
  }
  try {
    if (tokens.at(0) == "rcreate") {
      if (tokens.size() - 1 < 2) {
        return "Error: not enough arguments";
      }
      int taille = std::stoi(tokens.at(1));
      int vmax = std::stoi(tokens.at(2));
      routes.emplace_back(std::move(Route(vmax, 0, std::vector<Voiture>(taille))));
      currentRoute = static_cast<long>(routes.size()) - 1;
      routes.at(currentRoute).attachDebug(&debug);
    } else if (tokens.at(0) == "rselect") {
      if (tokens.size() - 1 < 1) {
        return "Error: not enough arguments";
      }
      int route = std::stoi(tokens.at(1));
      if (route < 0 || route >= routes.size()) {
        return "Error: route does not exist";
      }
      currentRoute = route;
    } else if (tokens.at(0) == "afficher") {
      if (currentRoute == -1) {
        return "Error: no route selected";
      }
      afficherR(routes.at(currentRoute));
      return debugOutput;
    } else if (tokens.at(0) == "ajouter") {
      if (currentRoute == -1) {
        return "Error: no route selected";
      }
      if (tokens.size() - 1 < 1) {
        return "Error: not enough arguments";
      }
      int posi = std::stoi(tokens.at(1));
      ajouter(routes.at(currentRoute), posi);
    } else if (tokens.at(0) == "simuler") {
      if (currentRoute == -1) {
        return "Error: no route selected";
      }
      if (tokens.size() - 1 < 1) {
        return "Error: not enough arguments";
      }
      int nbPas = std::stoi(tokens.at(1));
      simuler(routes.at(currentRoute), nbPas);
    } else if (tokens.at(0) == "savitesse") {
      if (currentRoute == -1) {
        return "Error: no route selected";
      }
      if (tokens.size() - 1 < 1) {
        return "Error: not enough arguments";
      }
      char nom = tokens.at(1).at(0);
      return std::to_string(saVitesse(routes.at(currentRoute), nom));
    } else if (tokens.at(0) == "freiner") {
      if (currentRoute == -1) {
        return "Error: no route selected";
      }
      freiner(routes.at(currentRoute));
    } else if (tokens.at(0) == "accelerer") {
      if (currentRoute == -1) {
        return "Error: no route selected";
      }
      accelerer(routes.at(currentRoute));
    } else if (tokens.at(0) == "supprimer") {
      if (currentRoute == -1) {
        return "Error: no route selected";
      }
      if (tokens.size() - 1 < 1) {
        return "Error: not enough arguments";
      }
      char nom = tokens.at(1).at(0);
      supprimer(routes.at(currentRoute), nom);
    } else if (tokens.at(0) == "rsuppr") {
      if (currentRoute == -1) {
        return "Error: no route selected";
      }
      routes.erase(routes.begin() + (int) currentRoute);
      currentRoute = -1;
    } else if (tokens.at(0) == "ralentir") {
      if (currentRoute == -1) {
        return "Error: no route selected";
      }
      ralentir(routes.at(currentRoute));
    } else if (tokens.at(0) == "deplacer") {
      if (currentRoute == -1) {
        return "Error: no route selected";
      }
      routes.at(currentRoute).deplacer();
    } else if (tokens.at(0) == "setrandalea") {
      if (currentRoute == -1) {
        return "Error: no route selected";
      }
      if (tokens.size() - 1 < 1) {
        return "Error: not enough arguments";
      }
      int randalea = std::stoi(tokens.at(1));
      if (randalea < 0 || randalea > 100) {
        return "Error: randalea must be between 0 and 100";
      }
      setPV(routes.at(currentRoute), (double)(randalea/100.0));
    }
  } catch (const std::exception &e) {
    return "Error: " + std::string(e.what());
  }

  return "";
}

void debug(const std::stringstream &s) {
  debugOutput += s.str();
}

} // testing