# Projet théorie des langages sur l'Automates
Ce dépôt est consacré au projet de la théorie des langages sur les automates, l'idée est de réaliser un programme en langage C permettant de lire et stocker en mémoire un automate A à partir d'un fichier .txt, et aussi implementer quelques algorithmes élémentaires de manipulation des automate

## Partie 1 :
Une structure de données permettant de stocker les informations d'un automate;
Une fonction permettant de lire et stocker un automate à partir d'un fichier.ex;
Une fonction permettant d'afficher l'ensemble de l'alphabet.

## Partie 2: 
Une fonction permettant de générer un fichier dot associé à un automate passé en paramètre et d'affichage sur l'écran le fichier png associé au fichier .dot.
-L'état initial est coloré en vert, les états finaux en bleu, les états inatteignables en gris et les autres états en noir.

## Partie 3 :
Une fonction permettant de tester si un mot M est engendré par un automate A. Le mot M et l'automate A sont les paramètres de cette fonction;
Une fonction permettant de lire le contenu du fichier Mots. txt et d'afficher la liste des mots engendrés par l'automate A passé en paramètre.

## Partie 4 :
Les fonctions suivantes :
-Union Automates : permettant de calculer l'union de automates passés en paramètres;
-Etoile_Automate : permettant de mettre à l'étoile un automate passé en paramètre;
-Produit_Automates : permettant de calculer le produit de deux automates passés en paramètres.

## Partie 5 :
Une fonction permettant de supprimer les & - transitions d'un automate passé en paramètre;
Une fonction permettant de retourner un automate déterministe associé à un automate passé en paramètre;
Une fonction permettant de retourner un automate minimal associé à un automate passé en paramètre.

