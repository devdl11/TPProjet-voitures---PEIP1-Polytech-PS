# Unit tests
Dans ce dossier ce trouve les tests unitaires de l'application.
Pour ce faire, nous avons implémenté un interpréteur customisé.

Pour un test, il faut écrire un fichier .in contenant le test à effectuer, et à mettre l'output attendu dans un fichier .out, ayant le même nom que le fichier .in.
(exemple: test.in et test.out)
Attention à ne pas oublier le retour à la ligne après chaque commande "afficher" (le système est sensible à la casse et au formatage).

Commandes disponibles:

 - ~commentaire: commentaire
 - afficher: appel de la fonction "afficherR"
 - rcreate [int] [int] : initialise une route avec une longueur et une vitesse, et la sélectionne
 - ajouter [int] : ajoute une voiture à partir de la position donnée
 - simuler [int] : effectue la simulation du modèle Nagel-Schrekenberg n fois
 - savitesse [char] : affiche la vitesse de la voiture nommée i (appel de la fonction saVitesse)
 - freiner : effectue l'étape 2 du modèle Nagel-Schrekenberg
 - accelerer : effectue l'étape 1 du modèle Nagel-Schrekenberg
 - supprimer [char] : supprime la voiture i de la route
 - rsuppr : supprime la route sélectionnée
 - ralentir : effectue l'étape 3 du modèle Nagel-Schrekenberg
 - deplacer : effectue l'étape 4 du modèle Nagel-Schrekenberg
 - setpv[int] : change la valeur de pv de la route sélectionnée. La variable doit avoir une valeur entre 0 et 100.
 - setvmax[int] : change la valeur de vmax de la route sélectionnée.
 (appel de la fonction setVMax)