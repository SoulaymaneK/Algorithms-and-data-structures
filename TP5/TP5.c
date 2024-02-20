//
// Created by Soulaymane  on 08/06/2023.
//

#include "TP5.h"

void empiler(Pile *pile,int valeur){
    Element *newelement = malloc(sizeof(Element));
    newelement->nombre = valeur;
    newelement->suivant = *pile;
    *pile = newelement;
}

int depiler(Pile *pile){
    if (pile==NULL){
        printf("La pile est vide.\n");
        return -1;
    }
    Element *dep_element = *pile;
    int val = dep_element->nombre;
    *pile = dep_element->suivant;
    free(dep_element);
    return val;
}

void afficher(Pile pile){
    Pile p = pile;
    while (p!=NULL){
        printf("%d\n",(p)->nombre);
        (p) = (p)->suivant;
    }
}

void echanger(Pile *pile){
    Element *premier = *pile;
    Element *precedent = *pile;
    Element *dernier = *pile;
    if (*pile != NULL){
        while (dernier->suivant != NULL){
            precedent = dernier;
            dernier = dernier->suivant;
        }
        dernier->suivant = premier->suivant;
        precedent->suivant = premier;
        premier->suivant = NULL;
        *pile = dernier;
    }
}

void insertion(Abr *a,int cle){
    Noeud *abr = *a;
    Noeud *pere = *a;

    Noeud *newn = malloc(sizeof(Noeud));
    newn->cle = cle;
    newn->fd = NULL;
    newn->fg = NULL;

    if (abr==NULL){
        (*a) = newn;
        return;
    }
    while (abr!=NULL){
        pere = abr;
        if (cle>=pere->cle){
            abr = abr->fd;
        } else{
            abr = abr->fg;
        }

        if (cle > pere->cle){
            pere->fd = newn;
        } else
            pere->fg = newn;
    }
}

void afficher2(Abr a){
    if (a==NULL){
        return;
    }
    afficher2(a->fg);
    printf("%d\n",a->cle);
    afficher2(a->fd);

}

int nombre_feuilles(Abr a){
    if (a!=NULL){
        if (a->fg == NULL && a->fd == NULL)
            return 1;
        else
            return nombre_feuilles(a->fg) + nombre_feuilles(a->fd);
    } else
        return 0;
}

int nombre_noeuds_internes(Abr a){
    if (a==NULL || (a->fg==NULL && a->fd==NULL))
        return 0;
    //printf("\n%d\n",a->cle);
    return 1 + nombre_noeuds_internes(a->fg) + nombre_noeuds_internes(a->fd);
}

void enfiler(File *file, int valeur){
    Element *new = malloc(sizeof(Element));
    new->nombre = valeur;
    new->suivant = NULL;

    if (file->debut==NULL) {
        file->debut = new;
        file->fin = new;
    } else {
        file->fin->suivant = new;
        file->fin = new;
    }
}


int defiler(File *file){
    if (file->debut==NULL)
        return -1;
    int valeur = file->debut->nombre;
    Element *e = file->debut;
    file->debut = e->suivant;
    free(e);
    return valeur;
}

void afficher3(File file){
    if(file.debut == NULL)
        return;
    Element *tete = file.debut;
    Element *queue = file.fin;
    printf("%d\n",tete->nombre);
    while (tete!=queue){
        tete = tete->suivant;
        printf("%d\n",tete->nombre);
    }
}

void inverser(File *file){
    if (file->debut==NULL)
        return;
    int data = defiler(file);
    inverser(file);
    enfiler(file,data);
}