
// GI_1 2023/2024, By Sadki Mohamed

// Read this before navigating the code!!!

//Hello, this code was done mainly by Mohamed Sadki, Nassim El Kaddaoui and Mohamed El Attaoui, students at the national school of applied sciences of Tetouan

//Our code is not perfect, Part 4 and 5 may have errors and are not complete!!

// Make sure to have the latest version of Graphviz in order to generate the PNG file

// The function name define its utility (lire_automate --> denotes reading the automate..etc)

// When we work with pointers ex: Automate *automate, we retrieve data like this : automate->etat_initial
// When we work with structures ex: Automate automate, we retrieve data like this : automate.etat_initial


// The code is open source, any modifications are welcomed,          Good luck in your Project!!





#include <stdio.h> // standard input output library
#include <stdlib.h>  // mainly used for the malloc, realloc and calloc functions (memory allocation functions)
#include <string.h> // library mainly used for string functions like strcmp, strcpy ..etc
#include <ctype.h> // mainly used for isalpha, isdigit..etc functions
#include <stdbool.h> // library for the boolean variables
#define ETAT_MAX 10 //defining a constant
int n_lignes, i,j,k,m,n,choix,choix_1,choix_2; // to avoid declaring them in every function specially i j k

// Part 1


// We define the structures that we're gonna use throughout the whole code
typedef struct Transition {
    int etat_depart;
    int etat_arrive;
    char etiquette_de_transition;
} Transition;

typedef struct Automate {
    int etat_initial[50];
    int etat_final[50];
    int n_etats_initiaux;
    int n_etats_finaux;
    int n_transitions;
    Transition *transitions; // we define a pointer to transitions, its type is Transition like int char but instead it's Transition (the structure)!
} Automate;

void lire_automate(char *nom_fichier, Automate *automate ) { // be careful with Automate *automate, this is a pointer! it needs memory allocation before using it!
    FILE *fichier = fopen(nom_fichier, "r");// opening the file, FILE is a predefined variable in stdio.h we use it always when we're working with files
    if (fichier == NULL) {
        printf("Il ya un erreur \n");
        exit(EXIT_FAILURE);}

        // reading file's lines
char A[40];
    n_lignes = 0;
    while (fgets(A, sizeof(A), fichier)) {
        n_lignes++;
    }
    rewind(fichier);// sets the file pointer at the beginning of the file, normally we need this when we read a file multiple times

    int ligne_1 = 1;
    char A1[40];
    while (fgets(A1, sizeof(A1), fichier)) {
        if (ligne_1 == (n_lignes - 1)) {
            automate->n_etats_initiaux = numero_in_chaine(A1);
        }
        ligne_1++;
    }
    rewind(fichier);

    int ligne_2 = 1;
    char A2[40];
    while (fgets(A2, sizeof(A2), fichier)) {
        if (ligne_2 == (n_lignes)) {
            automate->n_etats_finaux = numero_in_chaine(A2);
        }
        ligne_2++;
    }
    rewind(fichier);

    automate->transitions = (Transition *)malloc((n_lignes - 2) * sizeof(Transition));
 // when we use pointers, we normally need to allocate memory to avoid bad memory allocation, that why we avoided using them lately in the code in cases like declaring automate, we used structures instead !
    automate->n_transitions = n_lignes -2 ;
    for (i = 0; i < n_lignes - 2; i++) {
        fscanf(fichier, "%d %d %c", &automate->transitions[i].etat_depart,
                                    &automate->transitions[i].etat_arrive,
                                    &automate->transitions[i].etiquette_de_transition);
    }

    for (i = 0; i < automate->n_etats_initiaux; i++) {
        fscanf(fichier, "%d", &automate->etat_initial[i]);
    }
    for (i = 0; i < automate->n_etats_finaux; i++) {
        fscanf(fichier, "%d", &automate->etat_final[i]);
    }
    fclose(fichier);
}

int numero_in_chaine(char *str) { //this function check whether a string got number init or not
    int num = 0;
    for (i = 0; i < strlen(str); i++) {
        if (isdigit(str[i])) {
            num++;
        }
    }
    return num;
}

void afficher_transitions(Automate automate) {
    printf("\nVoici les transitions :\n");
    for ( i = 0; i < n_lignes - 2; i++) {
        printf("%d -> %d  :  %c\n", automate.transitions[i].etat_depart,
                                    automate.transitions[i].etat_arrive,
                                    automate.transitions[i].etiquette_de_transition);
    }
}

void afficher_etats_initiaux(Automate automate) {
    printf("\n Le nombre d'états initiaux : %d\n", automate.n_etats_initiaux);
   printf("\n les etats initiaux sont :  ");
    for ( i = 0; i < automate.n_etats_initiaux; i++) {
        printf("  %d  ", automate.etat_initial[i]);
    }
    printf("\n");
}

void afficher_etats_finaux(Automate automate) {
printf("\nLe nombre des états finaux : %d\n", automate.n_etats_finaux);
    printf("\n les etats finaux sont: ");
    for ( i = 0; i < automate.n_etats_finaux; i++) {
        printf("  %d  ", automate.etat_final[i]);
    }
       printf("\n");
}

void afficher_alphabet(Automate automate) {
    printf("\n les alphabets de l'automate :\n ");
    int alphabet[20] = {0};
    for ( i = 0; i < n_lignes - 2; i++) {
        if (isalpha(automate.transitions[i].etiquette_de_transition)) {
            char lettre = tolower(automate.transitions[i].etiquette_de_transition);// make all alphabets lowercase
            if (alphabet[lettre - 'a'] == 0) {
                alphabet[lettre - 'a'] = 1;
                printf("\n %c \n", lettre);
// this one is tricky, 'a' is the ASCII code of a ig 97 , alphabet[lettre - 'a'] check whether the position of the index lettre - 'a' is not filled yet
// if no, then it gonna fill it with 1 and print the letter, we use this If loop to avoid printing the same letter
// now let's understand lettre - 'a', for example the letter = b, the ASCII code of b is 98 so lettre - 'a' = 98-97 = 1, so we check alphabet[1] and so on...

                }}}
}


// Part 2

bool test_etat_final(Automate automate, int etat) {
    for ( i = 0; i < automate.n_etats_finaux; i++) {
        if (automate.etat_final[i] == etat) {
            return true;
        }
    }
    return false;
}

void generer_fichier_dot(Automate automate) {
    int etats_atteignables[200] = {0};
    int n_etats_atteignable;
    FILE *fichier;
    fichier = fopen("automate.dot", "w");

    fprintf(fichier, "digraph { \n"); // the .dot file should start with this otherwise it will not work properly!

    for ( i = 0; i < automate.n_etats_initiaux; i++) {
            etats_atteignables[i] = automate.etat_initial[i];
            fprintf(fichier, "%d [color=green];\n", automate.etat_initial[i]);
    }

    for ( i = 0; i < automate.n_etats_finaux; i++) {
        fprintf(fichier, "%d [color=blue];\n", automate.etat_final[i]);
    }

    n_etats_atteignable = automate.n_etats_initiaux;
     i = 0;

    while (i < n_etats_atteignable) {
        for ( j = 0; j < n_lignes -2; j++) {
            if (etats_atteignables[i] == automate.transitions[j].etat_depart) {
                etats_atteignables[n_etats_atteignable] = automate.transitions[j].etat_arrive;
                n_etats_atteignable++;
            }
        }
        i++;
    }
   int ett[30];
    int j = 0;
    for ( i = 0; i < n_lignes - 2; i++) {
        ett[j] = automate.transitions[i].etat_depart;
        ett[j + 1] = automate.transitions[i].etat_arrive;
        j = j + 2;
    }

    for ( j = 0; j < (n_lignes - 2) ; j++) {
        fprintf(fichier, "%d -> %d [label=\"%c\"];\n", automate.transitions[j].etat_depart,
                                                       automate.transitions[j].etat_arrive,
                                                       automate.transitions[j].etiquette_de_transition);
    }



for ( i = 0; i < (n_lignes - 2) * 2; i++) {
        int deja = 0;
         j = 0;
        while (j < n_etats_atteignable && deja == 0) {
            if (ett[i] == etats_atteignables[j]) {
                deja = 1;
            }
            j++;
        }
        if (deja == 0) {
            fprintf(fichier, "%d [color=gray];\n", ett[i]);
        }
    }


    fprintf(fichier, "}");
    fclose(fichier);
    system("dot -Tpng automate.dot -o automate.png");// here we generate the png file from .dot, it will be done automatically
    system("start automate.png");
}


// Part 3

bool test_mot(Automate automate, char mot[]) {
    int etat_act, k;
    bool test_1 = false;

    etat_act = automate.etat_initial[0];

    for ( i = 0; i < automate.n_etats_initiaux; i++) {
        for ( j = 0; j < strlen(mot); j++) {
            for ( k = 0; k < n_lignes - 2; k++) {
                if (automate.transitions[k].etat_depart == etat_act && automate.transitions[k].etiquette_de_transition == mot[j]) {
                    etat_act = automate.transitions[k].etat_arrive;
                    test_1 = true;
                    break;
                }
            }
            if (test_1 == false) {
                return false;
        }
        }
        }

    if (test_etat_final(automate, etat_act)== true) {
        return true;
        }

    return false;
}

void test_mot_entree(Automate automate)
{
char mot[50];

do {
  printf("Donner le mot que vouler vous tester :");
  scanf("%s", mot);
} while (isalpha(mot)== 1);

if (test_mot(automate, mot)== true) {
            printf("\n %s : est Engendrée \n", mot);
        } else {
            printf("\n %s : n'est pas Engendrée \n", mot);
        }

}

void test_fichier_mot(Automate automate, char* nom_fichier) {

  FILE* fichier = fopen(nom_fichier, "r");

    if (fichier == NULL) {
        printf(" Il ya un Erreur!");
        exit(1);
    }

    char mot[100];
    while (fscanf(fichier, "%s", mot) != EOF) {
        if (test_mot(automate, mot)== true) {
            printf("\n %s : est Engendrée \n", mot);
        } else {
            printf("\n %s : n'est pas Engendrée \n", mot);
        }
    }
    printf ("\n \n ");

    fclose(fichier);

}

// Part 4

void union_automate(Automate automate1, Automate automate2) {
    Automate union_automate;
    int i, j;

    union_automate.n_etats_initiaux = 2;
    union_automate.n_etats_finaux = 2;
    union_automate.n_transitions = automate1.n_transitions + automate2.n_transitions +
                                   automate1.n_etats_initiaux + automate2.n_etats_initiaux +
                                   automate1.n_etats_finaux + automate2.n_etats_finaux;

    union_automate.etat_initial[0] = 0;
    union_automate.etat_final[0] = 1;

    union_automate.transitions = (Transition *)malloc(union_automate.n_transitions * sizeof(Transition));
    if (union_automate.transitions == NULL) {
        printf("Erreur d'allocation mémoire\n");
        exit(EXIT_FAILURE);
    }

    for (i = 0; i < automate1.n_transitions; i++) {
        union_automate.transitions[i] = automate1.transitions[i];
    }

    for (i = 0; i < automate2.n_transitions; i++) {
        union_automate.transitions[automate1.n_transitions + i] = automate2.transitions[i];
        union_automate.transitions[automate1.n_transitions + i].etat_depart += automate1.n_etats_initiaux;
        union_automate.transitions[automate1.n_transitions + i].etat_arrive += automate1.n_etats_initiaux;
    }

    for (i = 0; i < automate1.n_etats_initiaux; i++) {
        Transition epsilon_transition;
        epsilon_transition.etat_depart = 0;
        epsilon_transition.etat_arrive = automate1.etat_initial[i] + 2;
        epsilon_transition.etiquette_de_transition = ' ';
        union_automate.transitions[automate1.n_transitions + i] = epsilon_transition;
    }
    for (i = 0; i < automate2.n_etats_initiaux; i++) {
        Transition epsilon_transition;
        epsilon_transition.etat_depart = 0;
        epsilon_transition.etat_arrive = automate2.etat_initial[i] + automate1.n_etats_initiaux + 2;
        epsilon_transition.etiquette_de_transition = ' ';
        union_automate.transitions[automate1.n_transitions + automate2.n_etats_initiaux + i] = epsilon_transition;
    }

    for (i = 0; i < automate1.n_etats_finaux; i++) {
        Transition epsilon_transition;
        epsilon_transition.etat_depart = automate1.etat_final[i] + 2;
        epsilon_transition.etat_arrive = 1;
        epsilon_transition.etiquette_de_transition = ' ';
        union_automate.transitions[automate1.n_transitions + automate2.n_transitions + i] = epsilon_transition;
    }
    for (i = 0; i < automate2.n_etats_finaux; i++) {
        Transition epsilon_transition;
        epsilon_transition.etat_depart = automate2.etat_final[i] + automate1.n_etats_initiaux + 2;
        epsilon_transition.etat_arrive = 1;
        epsilon_transition.etiquette_de_transition = ' ';
        union_automate.transitions[automate1.n_transitions + automate2.n_transitions + automate1.n_etats_finaux + i] = epsilon_transition;
    }

    printf("\nVoici les transitions de l'automate résultant :\n");
    for (i = 0; i < automate1.n_transitions + automate2.n_transitions; i++) {
        printf("%d -> %d  :  %c\n", union_automate.transitions[i].etat_depart,
                                    union_automate.transitions[i].etat_arrive,
                                    union_automate.transitions[i].etiquette_de_transition);
    }

    FILE *fichier_dot = fopen("union_automate.dot", "w");
    fprintf(fichier_dot, "digraph {\n");
    for (i = 0; i < automate1.n_transitions + automate2.n_transitions; i++) {
        fprintf(fichier_dot, "%d -> %d [label=\"%c\"];\n", union_automate.transitions[i].etat_depart,
                                                           union_automate.transitions[i].etat_arrive,
                                                           union_automate.transitions[i].etiquette_de_transition);
    }
    fprintf(fichier_dot, "}\n");
    fclose(fichier_dot);

    system("dot -Tpng union_automate.dot -o union_automate.png");
    system("start union_automate.png");

    free(union_automate.transitions);
}


void etoile_automate(char* nom_fichier, Automate automate_etoile) {
    int t = 0;
    FILE *fichier = fopen(nom_fichier, "r");
    if (fichier == NULL) {
        printf("Il ya un erreur \n");
        exit(EXIT_FAILURE);
    }

    char A[40];
    int n_lignes = 0;
    while (fgets(A, sizeof(A), fichier)) {
        n_lignes++;
    }
    rewind(fichier);

    int ligne_1 = 1;
    char A1[40];
    while (fgets(A1, sizeof(A1), fichier)) {
        if (ligne_1 == (n_lignes - 1)) {
            automate_etoile.n_etats_initiaux = numero_in_chaine(A1);
        }
        ligne_1++;
    }
    rewind(fichier);

    int ligne_2 = 1;
    char A2[40];
    while (fgets(A2, sizeof(A2), fichier)) {
        if (ligne_2 == (n_lignes)) {
            automate_etoile.n_etats_finaux = numero_in_chaine(A2);
        }
        ligne_2++;
    }
    rewind(fichier);

    automate_etoile.transitions = (Transition *)malloc((n_lignes - 2 + automate_etoile.n_etats_finaux) * sizeof(Transition));
    automate_etoile.n_transitions = n_lignes - 2;
    for ( i = 0; i < n_lignes - 2; i++) {
        fscanf(fichier, "%d %d %c", &automate_etoile.transitions[i].etat_depart,
                                    &automate_etoile.transitions[i].etat_arrive,
                                    &automate_etoile.transitions[i].etiquette_de_transition);
        t++;
    }

    for ( i = 0; i < automate_etoile.n_etats_initiaux; i++) {
        fscanf(fichier, "%d", &automate_etoile.etat_initial[i]);
    }
    for ( i = 0; i < automate_etoile.n_etats_finaux; i++) {
        fscanf(fichier, "%d", &automate_etoile.etat_final[i]);
    }

    for ( i = 0; i < automate_etoile.n_etats_finaux; i++) {
        automate_etoile.transitions[t].etat_depart = automate_etoile.etat_final[i];
        automate_etoile.transitions[t].etat_arrive = automate_etoile.etat_initial[0];
        automate_etoile.transitions[t].etiquette_de_transition = '$'; // $ is epsilon
        t++;
    }

     for ( i = 0; i < automate_etoile.n_etats_finaux; i++) {
        automate_etoile.transitions[t].etat_depart = automate_etoile.etat_initial[0];
        automate_etoile.transitions[t].etat_arrive = automate_etoile.etat_final[i];
        automate_etoile.transitions[t].etiquette_de_transition = '$';
        t++;
    }



    printf("\nVoici les transitions :\n");
    for ( i = 0; i < t; i++) {
        printf("  %d --> %d  :  %c\n", automate_etoile.transitions[i].etat_depart, automate_etoile.transitions[i].etat_arrive, automate_etoile.transitions[i].etiquette_de_transition);
    }
    FILE *fichier_dot = fopen("automate_etoile.dot", "w");
    fprintf(fichier_dot, "digraph {\n");
    for ( i = 0; i < t; i++) {
        fprintf(fichier_dot, "%d -> %d [label=\"%c\"];\n", automate_etoile.transitions[i].etat_depart,
                automate_etoile.transitions[i].etat_arrive, automate_etoile.transitions[i].etiquette_de_transition);
    }
    for ( i = 0; i < automate_etoile.n_etats_initiaux; i++) {
        fprintf(fichier_dot, "%d [color=green];\n", automate_etoile.etat_initial[i]);
    }
    for ( i = 0; i < automate_etoile.n_etats_finaux; i++) {
        fprintf(fichier_dot, "%d [color=blue];\n", automate_etoile.etat_final[i]);
    }

    fprintf(fichier_dot, "}\n");
    fclose(fichier_dot);

    system("dot -Tpng automate_etoile.dot -o automate_etoile.png");
    system("start automate_etoile.png");
    free(automate_etoile.transitions);
    fclose(fichier);
}


void produit_automate(Automate a1, Automate a2) {
    Automate automate_produit;
    automate_produit.n_etats_initiaux = a1.n_etats_initiaux * a2.n_etats_initiaux;
    automate_produit.n_etats_finaux = a1.n_etats_finaux * a2.n_etats_finaux;
    printf("\nLe nombre des etats initiaux : %d \n", automate_produit.n_etats_initiaux);
    printf("Le nombre des etats finaux : %d \n", automate_produit.n_etats_finaux);

     k = 0;
    printf("Le couple des etats initiaux :   ");
    for ( i = 0; i < a1.n_etats_initiaux; i++) {
        for ( j = 0; j < a2.n_etats_initiaux; j++) {
            automate_produit.etat_initial[k] = a1.etat_initial[i] * 1000 + a2.etat_initial[j];
            printf("(%d ,%d)   ", a1.etat_initial[i], a2.etat_initial[j]);
            k++;
        }
    }
    printf("\n");

    k = 0;
    printf("Le couple des etats finaux :   ");
    for ( i = 0; i < a1.n_etats_finaux; i++) {
        for ( j = 0; j < a2.n_etats_finaux; j++) {
            automate_produit.etat_final[k] = a1.etat_final[i] * 1000 + a2.etat_final[j];
            printf("(%d ,%d)   ", a1.etat_final[i], a2.etat_final[j]);
            k++;
        }
    }
    printf("\n");

    automate_produit.transitions = (Transition *)malloc((a1.n_transitions * a2.n_transitions) * sizeof(Transition));
    if (automate_produit.transitions == NULL) {
        printf("Erreur d'allocation mémoire \n");
        exit(EXIT_FAILURE);
    }

    printf(" \n \n Les valeur dans le PNG sont comme ceci : A00B == (A,B) \n \n ");
    printf(" \n \n Si la premiere valeur est egal a 0 cad : 000B == (0,B) le PNG affiche seulement B ! \n \n \n ");

    int index_transition = 0;
    printf("Voici les transitions :\n");
    for ( i = 0; i < a1.n_transitions; i++) {
        for ( j = 0; j < a2.n_transitions; j++) {
            automate_produit.transitions[index_transition].etat_depart = a1.transitions[i].etat_depart * 1000 + a2.transitions[j].etat_depart;
            automate_produit.transitions[index_transition].etat_arrive = a1.transitions[i].etat_arrive * 1000 + a2.transitions[j].etat_arrive;
            automate_produit.transitions[index_transition].etiquette_de_transition = a1.transitions[i].etiquette_de_transition;
            printf(" (%d, %d) --> (%d, %d) : %c\n", a1.transitions[i].etat_depart,
                   a2.transitions[j].etat_depart, a1.transitions[i].etat_arrive,
                   a2.transitions[j].etat_arrive, a1.transitions[i].etiquette_de_transition);
            index_transition++;
        }
    }

    FILE *fichier;
    fichier = fopen("produit_automate.dot", "w");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        exit(EXIT_FAILURE);
    }

    fprintf(fichier, "digraph { \n");

    for ( i = 0; i < automate_produit.n_etats_initiaux; i++) {
        fprintf(fichier, "%d [color=green];\n", automate_produit.etat_initial[i]);
    }

    for ( i = 0; i < automate_produit.n_etats_finaux; i++) {
        fprintf(fichier, "%d [color=blue];\n", automate_produit.etat_final[i]);
    }

    for ( j = 0; j < index_transition; j++) {
        fprintf(fichier, "%d -> %d [label=\"%c\"];\n", automate_produit.transitions[j].etat_depart,
                automate_produit.transitions[j].etat_arrive,
                automate_produit.transitions[j].etiquette_de_transition);
    }

    fprintf(fichier, "}");
    fclose(fichier);

    system("dot -Tpng produit_automate.dot -o automate.png");
    system("start automate.png");
}

 // Part 5

void determinisation(Automate a, Automate a1) {

bool test = true ;

    if ( a.n_etats_initiaux > 1) {
    test = false;
    }
    else {
    i = 0;
    j= i + 1;
    while (i< a.n_transitions && test == true ) {
        while (j< a.n_transitions && test == true ) {
            if (a.transitions[i].etat_depart == a.transitions[j].etat_depart &&
                a.transitions[i].etiquette_de_transition == a.transitions[j].etiquette_de_transition)
        test = false;
        }
        j++;
    }
      i++;
    }
    if (test == true) {
        printf(" \n  L'Automate est deja detirministe \n");
    }

int T_alph[10], T_etats[10][10],T[10];
int n_lettre = 0;
i=1;

T_alph[n_lettre] = a.transitions[0].etiquette_de_transition;

    while ( i < a.n_transitions ) {
        if (a.transitions[i].etiquette_de_transition != T_alph[n_lettre]) {
        n_lettre++;
        T_alph[n_lettre];
        i++;
        }
        else {
            i++;
        }
    }
    for(i=0; i < 10; i++) {
       for (j=0; j<10; j++){
        T_etats[i][j] = 0;
       }
    }
    for (i=0;i< a.n_etats_initiaux; i++) {
        T_etats[0][i]= a.etat_initial[i];
    }




// unfortunately we could not complete this part, it`s up to you guys!!





}

void supprimer_transitions_epsilon(Automate *automate) {
    int nb_transitions = automate->n_transitions;
    bool epsilon_present = true;

    while (epsilon_present) {
        epsilon_present = false;

        for ( i = 0; i < nb_transitions; i++) {
            if (automate->transitions[i].etiquette_de_transition == '$') {
                epsilon_present = true;

                for ( j = i; j < nb_transitions ; j++) {
                    automate->transitions[j] = automate->transitions[j + 1];
                }

                nb_transitions--;
            }
        }
    }

    automate->n_transitions = nb_transitions;



       FILE *fichier;
    fichier = fopen("automate_sans_epsilon.dot", "w");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        exit(EXIT_FAILURE);
    }

    fprintf(fichier, "digraph { \n");

    for ( i = 0; i < automate->n_etats_initiaux; i++) {
        fprintf(fichier, "%d [color=green];\n", automate->etat_initial[i]);
    }

    for ( i = 0; i < automate->n_etats_finaux; i++) {
        fprintf(fichier, "%d [color=blue];\n", automate->etat_final[i]);
    }

    for ( j = 0; j < automate->n_transitions; j++) {
        fprintf(fichier, "%d -> %d [label=\"%c\"];\n", automate->transitions[j].etat_depart,
                automate->transitions[j].etat_arrive,
                automate->transitions[j].etiquette_de_transition);
    }

    fprintf(fichier, "}");
    fclose(fichier);

    system("dot -Tpng automate_sans_epsilon.dot -o automate_sans_epsilon.png");
    system("start automate_sans_epsilon.png");
}


void minimisation_automate(Automate *automate) {

    int partition[automate->n_etats_initiaux + automate->n_etats_finaux][automate->n_etats_initiaux + automate->n_etats_finaux];
    int final_partition = 0;
    int non_final_partition = 1;
    for (i = 0; i < automate->n_etats_initiaux + automate->n_etats_finaux; i++) {
        if (test_etat_final(*automate, automate->etat_final[i]))
            partition[i][0] = final_partition;
        else
            partition[i][0] = non_final_partition;
    }

    int num_partitions = 2;
    int changes;
    do {
        changes = 0;

        for (i = 0; i < automate->n_etats_initiaux + automate->n_etats_finaux; i++) {
            for (j = i + 1; j < automate->n_etats_initiaux + automate->n_etats_finaux; j++) {
                if (partition[i][0] != partition[j][0]) {
                    bool distinguishable = false;
                    for (k = 0; k < automate->n_transitions; k++) {
                        if (partition[automate->transitions[k].etat_depart][0] == partition[i][0] &&
                            partition[automate->transitions[k].etat_arrive][0] == partition[j][0]) {
                            distinguishable = true;
                            break;
                        }
                        if (partition[automate->transitions[k].etat_arrive][0] == partition[i][0] &&
                            partition[automate->transitions[k].etat_depart][0] == partition[j][0]) {
                            distinguishable = true;
                            break;
                        }
                    }
                    if (distinguishable) {
                        partition[j][0] = num_partitions++;
                        changes++;
                    }
                }
            }
        }
    } while (changes);


    Automate minimized_automaton;
    minimized_automaton.n_etats_initiaux = 0;
    minimized_automaton.n_etats_finaux = 0;


    int final_counts[num_partitions];
    int non_final_counts[num_partitions];
    memset(final_counts, 0, sizeof(final_counts));
    memset(non_final_counts, 0, sizeof(non_final_counts));
    for (i = 0; i < automate->n_etats_initiaux + automate->n_etats_finaux; i++) {
        if (test_etat_final(*automate, automate->etat_final[i]))
            final_counts[partition[i][0]]++;
        else
            non_final_counts[partition[i][0]]++;
    }


    minimized_automaton.transitions = (Transition *)malloc(automate->n_transitions * sizeof(Transition));
    if (minimized_automaton.transitions == NULL) {
        printf("Erreur d'allocation mémoire\n");
        exit(EXIT_FAILURE);
    }
    minimized_automaton.n_transitions = automate->n_transitions;


    int current_state_mapping[num_partitions];
    for (i = 0; i < num_partitions; i++) {
        if (final_counts[i] > 0)
            minimized_automaton.etat_final[minimized_automaton.n_etats_finaux++] = i;
        for (j = 0; j < automate->n_transitions; j++) {
            if (partition[automate->transitions[j].etat_depart][0] == i) {
                minimized_automaton.transitions[j].etat_depart = i;
                minimized_automaton.transitions[j].etat_arrive = partition[automate->transitions[j].etat_arrive][0];
                minimized_automaton.transitions[j].etiquette_de_transition = automate->transitions[j].etiquette_de_transition;
            }
        }
    }


    printf("\nVoici les transitions de l'automate minimisé :\n");
    for (i = 0; i < minimized_automaton.n_transitions; i++) {
        printf("%d -> %d  :  %c\n", minimized_automaton.transitions[i].etat_depart,
                                    minimized_automaton.transitions[i].etat_arrive,
                                    minimized_automaton.transitions[i].etiquette_de_transition);
    }


    free(automate->transitions);


    automate->n_etats_initiaux = minimized_automaton.n_etats_initiaux;
    automate->n_etats_finaux = minimized_automaton.n_etats_finaux;
    automate->n_transitions = minimized_automaton.n_transitions;
    automate->transitions = minimized_automaton.transitions;
}




int menu_principale() {
printf("\nMenu:\n");
        printf("1. Automate simple\n");
        printf("2. L'union des Automates\n");
        printf("3. Etoile de l'Automate \n");
        printf("4. Produit des Automates\n");
        printf("5. Faire des operations sur l'Automate\n");
        printf("6. Quitter \n");
        printf(" \n Choix : ");
        scanf("%d", &choix);
        return choix;
}

int menu_secondaire_1(){
        printf("1. Afficher les transitions\n");
        printf("2. Afficher les états initiaux \n");
        printf("3. Afficher les états initiaux \n");
        printf("4. Afficher l'alphabet de l'automate\n");
        printf("5. Générer le fichier DOT et le fichier PNG\n");
        printf("6. Afficher les mots engendree d'un fichier \n");
        printf("7. Tester le mot \n");
        printf("8. Retourner\n");
        printf(" \n Choix : ");
        scanf("%d", &choix_1);
return choix_1;
}

int menu_secondaire_2(){

	    printf("\n 1.  Supprimer les epsilons transitions ");
	    printf("\n 2.  Determiniser un automate ");
	    printf("\n 3.  Minimiser un automate ");
	    printf("\n 4.  Retourner ");
	    printf("\n votre choix : ");
		scanf("%d",&choix_2);
		return choix_2 ;
}


int main() {
    char nom_fichier[40],nom_fichier_1[40],nom_fichier_2[40];
    Automate automate;
    Automate automate_1;
    Automate automate_2;
    Automate *automate_union;
    Automate automate_etoile;
  do {
        choix = menu_principale();
        switch (choix) {
            case 1:
                system("@cls");
                printf("\n Donner le nom du fichier : ");
                scanf("%s", nom_fichier);
                lire_automate(nom_fichier, &automate);
                do {
                    choix_1 = menu_secondaire_1();
                    switch (choix_1) {
                        case 1:
                            system("@cls");
                            afficher_transitions(automate);
                            break;
                        case 2:
                            system("@cls");
                            afficher_etats_initiaux(automate);
                            break;
                        case 3:
                            system("@cls");
                            afficher_etats_finaux(automate);
                            break;
                        case 4:
                            system("@cls");
                            afficher_alphabet(automate);
                            break;
                        case 5:
                            system("@cls");
                            generer_fichier_dot(automate);
                            break;
                        case 6:
                            system("@cls");
                            printf("\n Donner le fichier contenant les mots :");
                            scanf("%s", nom_fichier);
                            test_fichier_mot(automate, nom_fichier);
                            break;
                        case 7:
                            system("@cls");
                            test_mot_entree(automate);
                            break;
                        case 8:
                            system("@cls");
                            break;
                        default:
                            printf("\n Stp choisir une option valide.\n");
                            break;
                    }
                } while (choix_1 != 8);
                break;

            case 2:
                system("@cls");
                printf("\n Donner le fichier contenant l'automate 1 : ");
                scanf("%s", nom_fichier_1);
                lire_automate(nom_fichier_1, &automate_1);
                printf("\n Donner le fichier contenant l'automate 2 : ");
                scanf("%s", nom_fichier_2);
                lire_automate(nom_fichier_2, &automate_2);
                union_automate(automate_1, automate_2);
                break;

            case 3:
                system("@cls||clear");
                printf("\n Donner le nom du fichier : ");
                scanf("%s", nom_fichier);
                lire_automate(nom_fichier, &automate);
                etoile_automate(nom_fichier, automate);
                afficher_etats_initiaux(automate);
                afficher_etats_finaux(automate);
                break;

            case 4:
                system("@cls");
                printf("\n Donner le fichier contenant l'automate 1 : ");
                scanf("%s", nom_fichier_1);
                lire_automate(nom_fichier_1, &automate_1);
                printf("\n Donner le fichier contenant l'automate 2 : ");
                scanf("%s", nom_fichier_2);
                lire_automate(nom_fichier_2, &automate_2);
                produit_automate(automate_1, automate_2);
                break;

            case 5:
                system("@cls");
                printf("\n Donner le nom du fichier : ");
                scanf("%s", nom_fichier);
                lire_automate(nom_fichier, &automate);
                do {
                    choix_2 = menu_secondaire_2();
                    switch (choix_2) {
                        case 1:
                            system("@cls");
                            supprimer_transitions_epsilon(&automate);
                            afficher_transitions(automate);
                            break;
                        case 2:
                            system("@cls");
                            afficher_etats_initiaux(automate);
                            break;
                        case 3:
                            system("@cls");
                            minimisation_automate(&automate);
                            afficher_transitions(automate);
                            break;
                        case 4:
                            system("@cls");
                            break;
                        default:
                            printf("\n Stp choisir une option valide.\n");
                            break;
                    }
                } while (choix_2 != 4);
                break;

            case 6:
                printf("Au revoir !\n");
                break;

            default:
                printf("Choix non valide.\n");
                break;
        }
    } while (choix != 6);

    return 0;
}


