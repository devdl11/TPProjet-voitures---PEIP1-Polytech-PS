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
