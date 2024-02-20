//
// Created by Soulaymane  on 08/06/2023.
//
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

typedef struct Element{
    int nombre;
    struct Element *suivant;
}Element;

typedef Element *Pile;

void empiler(Pile *pile,int valeur);
int depiler(Pile *pile);
void afficher(Pile pile);
void echanger(Pile *pile);




typedef struct Noeud
{
    int cle;
    struct Noeud* fg;
    struct Noeud* fd;
}Noeud;

typedef Noeud* Abr;

void insertion(Abr *a,int cle);
void afficher2(Abr a);
int nombre_feuilles(Abr a);
int nombre_noeuds_internes(Abr a);



typedef struct File{
    Element *debut;
    Element *fin;
}File;

void emfiler(File *file,int valeur);
int defiler(File *file);
void afficher3(File file);
void inverser(File *file);

