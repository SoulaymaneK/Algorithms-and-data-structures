//
// Created by Soulaymane  on 14/06/2023.
//

#include "TP52.h"

void InsererSomment(T_Arbre *abr, int cle){
    Sommet *s = *abr;
    Sommet *pere = *abr;

    Sommet *news = malloc(sizeof(T_sommet));
    news->cle = cle;
    news->fd = NULL;
    news->fg = NULL;

    if (s==NULL){
        (*abr) = news;
        return;
    }

    while (s!=NULL){
        pere = s;
        if (pere->cle==cle){
            printf("\nLa cle existe déjà.\n");
            return;
        }
        if (cle> pere->cle){
            s = s->fd;
        } else{
            s = s->fg;
        }
    }
    if (cle > pere->cle)
        pere->fd = news;
    else
        pere->fg = news;
}

void afficherArbre(T_Arbre abr){
    if (abr==NULL){
        return;
    }
    afficherArbre(abr->fg);
    printf("%d\n",abr->cle);
    afficherArbre(abr->fd);
}

int calculerHauteur(T_Arbre abr) {
    // Cas de base : si l'arbre est vide (cas d'arrêt de la récursion)
    if (abr == NULL) {
        return 0;
    } else {
        // Récursivement calculer la hauteur des sous-arbres gauche et droit
        int hauteurGauche = calculerHauteur(abr->fg);
        int hauteurDroit = calculerHauteur(abr->fd);

        // Retourner la plus grande hauteur entre les sous-arbres gauche et droit, plus 1 pour tenir compte du nœud racine
        if (hauteurGauche > hauteurDroit) {
            return hauteurGauche + 1;
        } else {
            return hauteurDroit + 1;
        }
    }
}

T_Arbre supprimerSommet(T_Arbre arbre, int cle) {
    if (arbre == NULL)
        return arbre;

    // Recherche du sommet à supprimer dans le sous-arbre gauche ou droit
    if (cle < arbre->cle)
        arbre->fg = supprimerSommet(arbre->fg, cle);
    else if (cle > arbre->cle)
        arbre->fd = supprimerSommet(arbre->fd, cle);
    else {
        // Cas : le sommet à supprimer a été trouvé

        // Cas 1 : sommet sans enfant ou avec un seul enfant
        if (arbre->fg == NULL) {
            T_Arbre temp = arbre->fd;
            free(arbre);
            return temp;
        } else if (arbre->fd == NULL) {
            T_Arbre temp = arbre->fg;
            free(arbre);
            return temp;
        }

        // Cas 2 : sommet avec deux enfants
        T_Arbre temp = arbre->fd;
        while (temp->fg != NULL)
            temp = temp->fg;
        arbre->cle = temp->cle;
        arbre->fd = supprimerSommet(arbre->fd, temp->cle);
    }

    return arbre;
}
int maxArbre(T_Arbre arbre,int *max){
    if (arbre==NULL){
        return -1;
    }

    (*max) = arbre->cle;
    maxArbre(arbre->fd,max);
    return *max;
}

int minArbre(T_Arbre arbre, int *min){
    if (arbre==NULL)
        return -1;
    (*min) = arbre->cle;
    minArbre(arbre->fg,min);
    return *min;
}

void viderAbre(T_Arbre arbre){
    if (arbre==NULL){
        return;
    }
    viderAbre(arbre->fg);
    free(arbre);
    viderAbre(arbre->fd);
}