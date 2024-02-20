//
// Created by Soulaymane  on 14/06/2023.
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

typedef struct Sommet{
    int cle;
    struct Sommet *fg;
    struct Sommet *fd;
}Sommet;

typedef Sommet T_sommet;

typedef T_sommet *T_Arbre;

void InsererSomment(T_Arbre *abr, int cle);