// NF16 - TP 4 : Les Arbres Binaires de Recherche
// Auteurs : Soulaymane KEBLI et Mohamed TAHIRI
// Fichier de définition des structures et de déclaration des fonctions

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


// Constantes

#define MAX_PAR_MOT 50
#define MOTS_MAX 10000
#define PHRASES_MAX 5000
#define CARACTERES_MAX MAX_PAR_MOT * MOTS_MAX


// Couleurs pour affichage (séquences ANSI)
// Si ça ne fonctionne pas, mettez une chaîne vide "" à la place des constances ci-dessous

#define ROUGE "\033[1;31m"
#define VERT "\033[1;32m"
#define CYAN "\033[1;36m"
#define ITALIQUE "\033[3m"
#define RESET "\033[0m"



// Structures et types

typedef struct Position{
    int numeroLigne;
    int ordre;
    int numeroPhrase;
    struct Position* suivant;
} T_Position;

typedef struct Noeud{
    char* mot;
    int nbOccurrences;
    T_Position* listePositions;
    struct Noeud* filsGauche;
    struct Noeud* filsDroit;
} T_Noeud;

typedef struct Index{
    T_Noeud* racine;
    int nbMotsDistincts;
    int nbMotsTotal;
    // Ajout d'une liste de phrases pour faciliter l'affichage de la question 6
    char* phrases[PHRASES_MAX];
    int nbPhrases;
} T_Index;

// Structure ajoutée pour répondre à la question 7.
// Elle permet de stocker tous les mots à la suite dans une liste chaînée.
typedef struct Mot{
    char* mot;
    int numeroLigne;
    int ordre;
    int numeroPhrase;
    struct Mot* suivant;
} T_Mot;


// Fonctions de base de l'énoncé

T_Position* ajouterPosition(T_Position* listeP, int ligne, int ordre, int numeroPhrase);

int ajouterOccurrence(T_Index *index, char *mot, int ligne, int ordre, int phrase);

int indexerFichier(T_Index *index, char *filename);

void afficherIndex(T_Index index);

T_Noeud* rechercherMot(T_Index index, char *mot);

void afficherOccurrencesMot(T_Index index, char *mot);

void construireTexte(T_Index index, char *filename);



// Fonctions utilitaires ajoutées

void viderBuffer();

int estLettres(char *mot);

void minuscules(char *mot);

char* capitaliser(char* mot);

char* partieAvant(char* mot);

char* partieApres(char* mot);

char* ajoutEspacePhrase(char* phrase);

T_Position* creerPosition(int numeroLigne, int ordre, int numeroPhrase);

T_Noeud* creerNoeud(char *mot);

T_Index* creerIndex();

T_Mot* creerMot(char* mot, int numeroLigne, int ordre, int numeroPhrase);

void afficherMot(T_Noeud *noeud);

void remplirTableauNoeuds(T_Noeud* noeud, T_Noeud** listeMots, int* nbMots);

void ajouterMot(T_Mot *listeMots, char* mot, int numeroLigne, int ordre, int numeroPhrase);

void remplirTableauMots(T_Noeud *noeud, T_Mot *listeMots);

