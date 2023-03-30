# Voitures - Mini Projet
URL : https://github.com/devdl11/tp3-voitures
## Authors
- Ladrem Yanni
- Luca David

## Compte rendu : 
### 1. Création du projet
Nous avons commencé par réecrire le projet en séparant dans un premier temps les fonctions dans des fichiers différents
en fonction de leur fonction. 
### 2. Séparation des fichiers
Ainsi, nous sommes passé de 2 fichiers (voitures.cpp voitures.h) à deux fichiers Nasch, regroupant ici la définition et
l'implémentations des fonctions, deux fichiers tracing, ayant ici les fonctions pour l'output pour le debug ainsi que la 
variable DEBUG permettant de set l'activation ou non du debug.
Enfin, nous avons écrit les sources nasch_test (cpp et h), faisant office de passerelle entre les tests officiels et notre code.
Ainsi, nous gardons une compatibilité avec les tests déjà existants sans devoir les modifier.

### 3. Création des tests (interpréteur)

Puis, nous avons créé les sources tests (cpp et h) qui contiennent les tests officiels ainsi qu'un système interpréteur permettant
de charger dynamiquement les tests présents dans un dossier unitTests et de les tester (dans le in, nous avons les instructions,
le .out l'output attendu dans la console).

Enfin, dans le main nous avons écrit le code lançant les tests et affichant les résultats.

### 4. Dispatching 
Dans un premier temps, Yanni s'est occupé de résoudre les fonctions de bases de manière simple. Puis, David s'est occupé de chercher 
des moyens d'optimisation. Enfin, nous avons vu ensemble la découpe et la création de l'interpréteur.
Yanni s'est occupé de documenter le code et d'écrire la documentation de l'interpréteur.

Nous avons conscience qu'il y a encore des choses pouvant être optimisé (utiliser le tableau ascii avec des intervalles au lieu d'une liste de caractères hardcodée),
mais nous avons décidé de rester sur une version fonctionnelle déjà bien complexe et répondant aux demandes du sujet.