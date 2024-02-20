//
// Created by KEBLI Soulaymane  on 15/06/2023.
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

typedef struct Restaurant{
    char *nom;
    float note;
    struct Restaurant *suivant;
}Restaurant;

typedef Restaurant T_Restaurant;

typedef Restaurant *T_Liste;

T_Liste ajouter_Restaurant(T_Liste ListResto, char *nom_R, float note);
T_Liste supprimer_Restaurant(T_Liste ListResto, char *nom_R);
void afficher_Restaurant(T_Liste ListResto);
T_Liste supprimer_Liste(T_Liste ListResto);

/*
 *Exercice 2
 */

typedef struct Noeud{
    char *nom_Region;
    T_Liste list_resto;
    struct Noeud *fg;
    struct Noeud *fd;
}Noeud;

typedef Noeud T_Noeud;

typedef Noeud *T_Arbre;


void nouveau_resto(T_Arbre abr,char *nom_Region,char *nom_Restaurant, float note);
void liste_regions(T_Arbre abr);
void liste_resto(T_Arbre abr, char* region);
T_Arbre supprimer_region(T_Arbre abr, char *region);
void viderArbre(T_Arbre abr);