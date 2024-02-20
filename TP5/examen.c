//
// Created by KEBLI Soulaymane  on 15/06/2023.
//

#include "examen.h"

T_Liste ajouter_Restaurant(T_Liste ListResto, char *nom_R, float note){
    if (note<0 || note>5){
        printf("\nLa note doit être compris entre 0 et 5.\n");
        return ListResto;
    }

    Restaurant *newr = malloc(sizeof(Restaurant));
    newr->nom = malloc(sizeof(strlen(nom_R)+1));
    strcpy(newr->nom,nom_R);
    newr->note = note;
    newr->suivant = NULL;

    T_Liste l = ListResto;

    if (l==NULL){
        newr->suivant = l;
        return newr;
    }

    while (l->suivant!=NULL && l->note>newr->note){
        if (strcmp(l->nom,newr->nom)==0){
            l->note = note;
            return ListResto;
        }
        l = l->suivant;
    }

    newr->suivant = l->suivant;
    l->suivant = newr;
    return ListResto;
}

T_Liste supprimer_Restaurant(T_Liste ListResto, char *nom_R){
    if (ListResto==NULL)
        return NULL;

    T_Liste l = ListResto;
    T_Liste precedent = ListResto;

    while (l!=NULL && strcmp(nom_R,l->nom)!=0){
        precedent = l;
        l = l ->suivant;
    }
    if (l==NULL && strcmp(precedent->nom,nom_R)!=0){
        printf("\nLe restaurant ne se trouve pas dans la liste!\n");
        return ListResto;
    }
    precedent->suivant = l->suivant;
    return ListResto;
}

void afficher_Restaurant(T_Liste ListResto){
    if (ListResto==NULL){
        printf("\nAucun restaurant dans la liste!\n");
        return;
    }
    T_Liste l = ListResto;
    int i = 1;
    while (l!=NULL){
        printf("%d - %s, note : %.2f\n",i,l->nom,l->note);
        l = l->suivant;
        i++;
    }
}

T_Liste supprimer_Liste(T_Liste ListResto) {
    if (ListResto == NULL) {
        return NULL;
    }

    /*T_Liste l = ListResto->suivant;
    supprimer_Liste(l);
    free(ListResto->nom);
    free(ListResto);*/

    T_Liste l = ListResto;
    while (ListResto != NULL) {
        l = ListResto;
        ListResto = ListResto->suivant;
        free(l->nom);
        free(l);
    }
    free(ListResto);
    return ListResto;
}

/*
 * EXERCICE 2
 * Dans cette partie il y' a un petit soucis avaec la fonction nouveau_resto
 * Sinon tout le reste est censé fonctionner correctement
 */

void nouveau_resto(T_Arbre abr,char *nom_Region,char *nom_Restaurant, float note){

    T_Noeud *newn  = malloc(sizeof(Noeud));
    newn->nom_Region = malloc(sizeof(strlen(nom_Region)+1));
    newn->list_resto = malloc(sizeof(T_Liste));
    strcpy(newn->nom_Region,nom_Region);
    newn->list_resto = ajouter_Restaurant(newn->list_resto,nom_Restaurant,note);
    newn->fd = NULL;
    newn->fg = NULL;

    T_Arbre a = abr;
    T_Arbre pere = abr;


    if (abr==NULL){
         abr = newn;
        return;
    }

    while (a!=NULL){
        pere = a;
        if (strcmp(pere->nom_Region,nom_Region)==0) {//si la region existe deja on ajoute seulement le restaurant et on sort
            a->list_resto = ajouter_Restaurant(a->list_resto, nom_Restaurant, note);
            return;
        }
        if (strcmp(newn->nom_Region,a->nom_Region)>0)//
            a = a->fd;
        else if (strcmp(newn->nom_Region,a->nom_Region)<0)
            a = a->fg;
    }
    if (strcmp(newn->nom_Region,pere->nom_Region)>0){
        pere->fd = newn;
    } else{
        pere->fg = newn;
    }
}

//on fait un parcours infixe pour les avoir dans l'ordre croissant
void liste_regions(T_Arbre abr){
    if (abr==NULL)
        return;
    liste_regions(abr->fg);
    printf("\n%s\n",abr->nom_Region);
    liste_regions(abr->fd);
}

void liste_resto(T_Arbre abr, char* region){
    if (abr==NULL){
        printf("\nL'arbre est vide.\n");
        return;
    }

    T_Arbre a = abr;
    while (a!=NULL && strcmp(a->nom_Region,region)!=0){
        if (strcmp(region,a->nom_Region)>0)
            a = a->fd;
        else if (strcmp(region,a->nom_Region)<0)
            a = a->fg;
    }
    if (a== NULL){
        printf("La region n'existe pas.\n");
        return;
    }

    afficher_Restaurant(a->list_resto);
}


T_Arbre supprimer_region(T_Arbre abr, char *region){
    if (abr==NULL)
        return NULL;
    //cette partie sert à charcher la bonne region à supprimer
    if (strcmp(region,abr->nom_Region)>0)
        abr->fd = supprimer_region(abr->fd,region);
    else if(strcmp(region,abr->nom_Region)<0)
        abr->fg = supprimer_region(abr->fg,region);
    //lorsqu'on l'a trouver
    else{
        if (abr->fd==NULL){//si elle possede que 1 fils gauche
            T_Arbre temp = abr->fg;
            supprimer_Liste(abr->list_resto);
            free(abr);
            return temp;
        }
        else if(abr->fg==NULL){//si elle possede que 1 fils droit
            T_Arbre temp = abr->fd;
            supprimer_Liste(abr->list_resto);
            free(abr);
            return temp;
        } else{//si elle possede 2 fils
            T_Arbre temp = abr->fd;
            while (temp->fg!=NULL)
                temp = temp->fg;
            strcpy(abr->nom_Region,temp->nom_Region);
            abr->fd = supprimer_region(abr->fd,temp->nom_Region);
        }
    }
    return abr;
}

//parcours infixe en supprimant chaque noeud et leur liste_resto
void viderArbre(T_Arbre abr){
    if (abr==NULL) {
        free(abr);
        return;
    }
    viderArbre(abr->fg);
    supprimer_Liste(abr->list_resto);
    free(abr);
    viderArbre(abr->fd);
}
