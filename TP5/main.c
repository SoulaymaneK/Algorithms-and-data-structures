//
// Created by Soulaymane  on 08/06/2023.
//
#include "TP5.c"

int main(){
   Pile p = NULL;

    //test empiler
    for (int i = 1; i <=20; ++i) {
        empiler(&p,i);
    }
    //test afficher
    afficher(p);

    //test depiler
    //for (int i = 1; i <= 20; ++i) {
      //  if (p!=NULL) printf("\n%d", depiler(&p));
   // }

    //test echange
    echanger(&p);
    afficher(p);

    Abr *a = malloc(sizeof(Abr));

    insertion(a,12);
    insertion(a,6);
    insertion(a,14);
    afficher2(*a);
    printf("\n%d",nombre_feuilles(*a));
    printf("\n%d\n",nombre_noeuds_internes(*a));

    File *f = malloc(sizeof(File));
    enfiler(f,1);
    enfiler(f,2);
    afficher3(*f);
    inverser(f);
    afficher3(*f);



}