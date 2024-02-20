#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tp3.h"


/* **********************************
 * Création et initialisation Produit
 ********************************** */
T_Produit *creerProduit(char *designation, float prix, int quantite) {
    T_Produit *nouveauProduit = NULL;

    nouveauProduit = malloc(sizeof(T_Produit));
    if (nouveauProduit != NULL) {
        // l'allocation mémoire s'est bien passée
        nouveauProduit->designation = malloc(strlen(designation) + 1); // Important : malloc permet d'avoir l'espace mémoire dédié pour notre champ de structure
        strcpy(nouveauProduit->designation,designation);
        nouveauProduit->prix = prix;
        nouveauProduit->quantite_en_stock = quantite;
        nouveauProduit->suivant = NULL;
    }

    return nouveauProduit;
}



/* ********************************
 * Création et initialisation Rayon
 ******************************** */
T_Rayon *creerRayon(char *nom) {
    T_Rayon *nouveauRayon = NULL;

    nouveauRayon = malloc(sizeof(T_Rayon));
    if (nouveauRayon != NULL) {
        // l'allocation mémoire s'est bien passée
        nouveauRayon->nom_rayon = malloc(strlen(nom) + 1);
        strcpy(nouveauRayon->nom_rayon,nom);
        nouveauRayon->liste_produits = NULL;
        nouveauRayon->suivant = NULL;
    }

    return nouveauRayon;
}



/* **********************************
 * Création et initialisation Magasin
 ********************************** */
T_Magasin *creerMagasin(char *nom) {
    T_Magasin *nouveauMagasin = NULL;

    nouveauMagasin = malloc(sizeof(T_Magasin));
    if (nouveauMagasin != NULL) {
        nouveauMagasin->nom = malloc(strlen(nom) + 1);
        strcpy(nouveauMagasin->nom,nom);
        nouveauMagasin->liste_rayons = NULL;
    }

    return nouveauMagasin;
}



/* ********************************
 * Ajout d'un rayon dans un magasin
 ******************************** */
int ajouterRayon(T_Magasin *magasin, char *nomRayon) {

    T_Rayon *nouveau_rayon = creerRayon(nomRayon);

    if (nouveau_rayon == NULL)
        return 0; // erreur malloc

    // Si le magasin est vide, on ajoute le rayon en tête de liste
    if (magasin->liste_rayons == NULL) {
        magasin->liste_rayons = nouveau_rayon;
        return 1;
    }

    else {

        T_Rayon *rayon = magasin->liste_rayons;
        T_Rayon *rayon_precedent = NULL;

        // On parcourt la liste des rayons jusqu'à trouver rayon = rayon qui vient après nouveau_rayon
        // et on en déduit rayon_precedent = rayon qui vient avant nouveau_rayon
        // strcmp permet de comparer deux chaînes de caractères en fonction de leur ordre alphabétique
        while (rayon != NULL && strcmp(rayon->nom_rayon, nomRayon) < 0) {
            rayon_precedent = rayon;
            rayon = rayon->suivant;
        }

        // Si le nom de rayon existe déjà, on retourne 0
        if (rayon != NULL && strcmp(rayon->nom_rayon, nomRayon) == 0)
            return 0;

        // Dans le cas où le rayon est le premier de la liste
        if (rayon_precedent == NULL) {
            nouveau_rayon->suivant = magasin->liste_rayons;
            magasin->liste_rayons = nouveau_rayon;
        }
            // Sinon, on ajoute le rayon à sa place entre les rayons
        else {
            nouveau_rayon->suivant = rayon;
            rayon_precedent->suivant = nouveau_rayon;
        }

    }

    return 1;
}



/* ********************************
 * Ajout d'un produit dans un rayon
 ******************************** */
int ajouterProduit(T_Rayon *rayon, char *designation, float prix, int quantite) {

    T_Produit *nouveau_produit = creerProduit(designation, prix, quantite);

    if (nouveau_produit == NULL)
        return 0; // Erreur malloc

    if (prix < 0 || quantite < 0)
        return 0; // Erreur prix ou quantité

    T_Produit *produit = rayon->liste_produits;

    while (produit != NULL) {
        if (strcmp(produit->designation, designation) == 0)
            return 0; // Produit déjà existant
        produit = produit->suivant;
    }

    produit = rayon->liste_produits;
    T_Produit *precedent = NULL;

    if (produit == NULL) {
        // Le rayon est vide, on insère le nouveau produit en tête de liste
        rayon->liste_produits = nouveau_produit;
        return 1;
    }

    // On trie par ordre croissant :

    while (produit != NULL && produit->prix < prix) {
        precedent = produit;
        produit = produit->suivant;
    }

    // On insère le nouveau produit dans la liste
    if (precedent == NULL) {
        // Le nouveau produit est le premier de la liste
        nouveau_produit->suivant = rayon->liste_produits;
        rayon->liste_produits = nouveau_produit;
    } else {
        // Le nouveau produit est inséré entre produit_précédent et produit
        nouveau_produit->suivant = produit;
        precedent->suivant = nouveau_produit;
    }

    return 1;
}



/* *****************************************
 * Affichage de tous les rayons d'un magasin
 ***************************************** */
void afficherMagasin(T_Magasin *magasin) {

    if (magasin == NULL) {
        printf("Il faut commencer par créer un magasin.");
        return;
    }

    T_Rayon *rayon = magasin->liste_rayons;

    printf("----- Liste des rayons du magasin ----\n");

    if (rayon == NULL) {
        printf("Le magasin est vide.");
        return;
    }

    // Afficher les rayons en tableau de la forme (nom du rayon, nombre de produits dans le rayon)
    printf("--------------------------------------\n");
    printf("| Nom du rayon\t|\tNombre de produits\n");
    printf("--------------------------------------\n");
    while (rayon != NULL) {

        // Partie pour rendre le tableau homogène
        char ajout_nom[S_MAX];
        for (int i = 0; i < S_MAX; i++)
        {
            ajout_nom[i] = ' ';
        }

        int nb_ajout = strlen("Nom du rayon") - strlen(rayon->nom_rayon);

        if (nb_ajout < 0)
            nb_ajout = 0;

        ajout_nom[nb_ajout] = '\0';

        printf("| %s%s\t|\t%d\n",
              rayon->nom_rayon, ajout_nom, nombre_produits(rayon));

        rayon = rayon->suivant;

    }
    printf("--------------------------------------\n");
}



/* *****************************************
 * Affichage de tous les produits d'un rayon
 ***************************************** */
void afficherRayon(T_Rayon *rayon) {

    T_Produit *produit = rayon->liste_produits;

    if (produit == NULL) {
        printf("\nLe rayon est vide.");
        return;
    }

    printf("----------- Liste des produits du rayon ----------\n");

    // Afficher les rayons en tableau de la forme (nom du rayon, nombre de produits dans le rayon)
    printf("--------------------------------------------------\n");
    printf("| Désignation\t|\tPrix \t|\tQuantité en stock\n");
    printf("--------------------------------------------------\n");

    while (produit != NULL) {

        // Partie pour rendre le tableau homogène
        char ajout_nom[S_MAX];
        for (int i = 0; i < S_MAX; i++)
        {
            ajout_nom[i] = ' ';
        }

        int nb_ajout = strlen("Désignation") - strlen(produit->designation);

        if (nb_ajout < 0)
            nb_ajout = 0;

        ajout_nom[nb_ajout] = '\0';

        printf("| %s%s\t|\t%0.2f€\t|\t%d\n",
               produit->designation, ajout_nom, produit->prix, produit->quantite_en_stock);

        produit = produit->suivant;

    }
    printf("--------------------------------------------------\n");
}



/* **************************************
* Suppression d'un produit dans un rayon
************************************** */
int supprimerProduit(T_Rayon *rayon, char* designation_produit) {
    T_Produit *produit = rayon->liste_produits;

    // Si le rayon est vide, on ne peut pas supprimer de produit
    if (produit == NULL) {
        printf("\nLe rayon est vide.");
        return 0;
    }

    // Si le produit à supprimer est le premier de la liste
    if (strcmp(produit->designation, designation_produit) == 0) {
        rayon->liste_produits = produit->suivant;
        free(produit);
        return 1;
    }

    T_Produit *produit_precedent = produit;

    while (produit != NULL) {
        if (strcmp(produit->designation, designation_produit) == 0) {
            produit_precedent->suivant = produit->suivant;
            free(produit);
            return 1;
        }
        produit_precedent = produit;
        produit = produit->suivant;
    }

    // Le produit n'existe pas.
    return 0;
}



/* *************************************************************
 * Suppression d'un rayon et de tous les produits qu'il contient
 ************************************************************* */
int supprimerRayon(T_Magasin *magasin, char *nom_rayon) {

    T_Rayon *rayon = chercher_rayon_par_nom(magasin, nom_rayon);

    if (rayon == NULL)
        return 0;

    T_Rayon *rayon_precedent = NULL;

    // Si le rayon est le premier de la liste
    if (rayon == magasin->liste_rayons) {
        magasin->liste_rayons = rayon->suivant;
    }
    else {
        rayon_precedent = magasin->liste_rayons;
        // On coupe la liste quand on arrive à rayon.
        while (rayon_precedent->suivant != rayon) {
            rayon_precedent = rayon_precedent->suivant;
        }

        rayon_precedent->suivant = rayon->suivant;
    }

    // On libère l'espace alloué pour chaque produit du rayon
    T_Produit *produit = rayon->liste_produits;
    T_Produit *produit_suivant;

    while (produit != NULL) {
        produit_suivant = produit->suivant;
        free(produit);
        produit = produit_suivant;
    }

    // On libère l'espace alloué par le rayon
    free(rayon);

    return 1;
}



/* **************************************************************************************
 * Recherche des produits se situant dans une fourchette de prix entrée par l'utilisateur
 ************************************************************************************** */
void rechercheProduits(T_Magasin *magasin, float prix_min, float prix_max) {

    T_Rayon *rayon = magasin->liste_rayons;

    if (rayon == NULL) {
        printf("\nLe magasin est vide.");
        return;
    }

    // Cette structure est juste une liste chaînée de produits
    // qui stocke le nom du rayon de chaque produit.
    T_Produit_Recherche *produit_recherche = NULL;

    while (rayon != NULL) {

        T_Produit *produit = rayon->liste_produits;

        while (produit != NULL && produit->prix <= prix_max) {

            if (produit->prix >= prix_min) {
                if (produit_recherche == NULL)
                    produit_recherche = creer_produit_recherche(produit, rayon->nom_rayon);
                else
                    ajouter_produit_recherche(produit_recherche, produit, rayon->nom_rayon);
            }

            produit = produit->suivant;
        }

        rayon = rayon->suivant;
    }

    printf("\n------------------ Liste des produits -------------------\n");

    printf("----------------- %0.2f€ < Prix < %0.2f€ ----------------\n", prix_min, prix_max);

    if (produit_recherche == NULL) {
        printf("\nAucun produit ne correspond à votre recherche.");
        return;
    }

    printf("| Marque (Désignation) | Prix | Quantité en stock | Rayon\n");

    while (produit_recherche != NULL) {

        // Partie pour rendre le tableau homogène
        char ajout_nom[S_MAX];
        for (int i = 0; i < S_MAX; i++)
        {
            ajout_nom[i] = ' ';
        }

        int nb_ajout = strlen("Marque(Désignation)") - strlen(produit_recherche->produit->designation);

        if (nb_ajout < 0)
            nb_ajout = 0;

        ajout_nom[nb_ajout] = '\0';

        printf("| %s%s | %0.2f | %d"
               "                | %s\n",
               produit_recherche->produit->designation,
               ajout_nom,
               produit_recherche->produit->prix,
               produit_recherche->produit->quantite_en_stock,
               produit_recherche->nom_rayon);

        T_Produit_Recherche *produit_recherche_a_supprimer = produit_recherche;
        produit_recherche = produit_recherche->suivant;
        free(produit_recherche_a_supprimer);
    }

    printf("---------------------------------------------------------\n");
}



/* *********************
 * Fusionner deux rayons
 ********************* */
void fusionnerRayons(T_Magasin *magasin) {

    // On demande les informations sur les 2 rayons

    char nom_rayon[50];

    if (magasin->liste_rayons == NULL) {
        printf("\nIl n'y a pas de rayons dans le magasin.");
        return;
    }

    if (magasin->liste_rayons->suivant == NULL) {
        printf("\nIl n'y a qu'un seul rayon dans le magasin.");
        return;
    }

    printf("\nQuels rayons voulez-vous fusionner ?\n");
    afficherMagasin(magasin);
    printf("\nPremier rayon : ");
    scanf(" %[^\n]", nom_rayon);
    viderBuffer();

    T_Rayon* rayon_9_1 = chercher_rayon_par_nom(magasin, nom_rayon);

    printf("Deuxième rayon : ");
    scanf(" %[^\n]", nom_rayon);
    viderBuffer();

    T_Rayon* rayon_9_2 = chercher_rayon_par_nom(magasin, nom_rayon);

    if (rayon_9_1 == NULL || rayon_9_2 == NULL) {
        printf("\nUn des rayons n'existe pas.");
        return;
    }

    if (rayon_9_1 == rayon_9_2) {
        printf("\nLes rayons sont identiques.");
        return;
    }

    printf("\nQuel est le nouveau rayon du rayon ? ");
    scanf(" %[^\n]", nom_rayon);
    viderBuffer();


    if (chercher_rayon_par_nom(magasin, nom_rayon) != NULL) {
        printf("\nCe nom de rayon est déjà utilisé.");
        return;
    }

    T_Produit *produit_9_1 = rayon_9_1->liste_produits;
    T_Produit *produit_9_2 = rayon_9_2->liste_produits;

    if (produit_9_1 == NULL || produit_9_2 == NULL) {
        printf("\nUn des rayons est vide.");
        return;
    }

    // On crée le nouveau rayon
    ajouterRayon(magasin, nom_rayon);
    T_Rayon *rayon_9_3 = chercher_rayon_par_nom(magasin, nom_rayon);

    if (rayon_9_3 == NULL) {
        printf("\nLe rayon n'a pas pu être créé.");
        return;
    }

    if (produit_9_1->prix < produit_9_2->prix) {
        rayon_9_3->liste_produits = creerProduit(produit_9_1->designation, produit_9_1->prix, produit_9_1->quantite_en_stock);

        rayon_9_3->liste_produits->suivant = NULL;
        produit_9_1 = produit_9_1->suivant;
    }
    else {
        rayon_9_3->liste_produits = creerProduit(produit_9_2->designation, produit_9_2->prix, produit_9_2->quantite_en_stock);
        rayon_9_3->liste_produits->suivant = NULL;
        produit_9_2 = produit_9_2->suivant;
    }

    // T_Produit *produit_9_3 = rayon_9_3->liste_produits;

    // On ajoute progressivement chaque produit dans le nouveau rayon
    // Le nombre d'opérations est réduit car on ne parcourt pas les deux listes en même temps

    // On n'utilise pas la fonction ajouterProduit car elle cherche la place du produit dans le rayon
    // (inutile dans notre cas car on ajoute les produits dans l'ordre croissant)

    while (produit_9_1 != NULL && produit_9_2 != NULL) {
        if (produit_9_1->prix < produit_9_2->prix) {
            ajouter_produit_fin(rayon_9_3, produit_9_1);
            produit_9_1 = produit_9_1->suivant;
        }
        else {
            ajouter_produit_fin(rayon_9_3, produit_9_2);
            produit_9_2 = produit_9_2->suivant;
        }
    }

    // On ajoute les produits manquants

    while (produit_9_1 != NULL) {
        ajouter_produit_fin(rayon_9_3, produit_9_1);
        produit_9_1 = produit_9_1->suivant;
    }

    while (produit_9_2 != NULL) {
        ajouter_produit_fin(rayon_9_3, produit_9_2);
        produit_9_2 = produit_9_2->suivant;
    }

    // On vérifie si les deux rayons ont bien été supprimés.

    int check = supprimerRayon(magasin, rayon_9_1->nom_rayon);

    check += supprimerRayon(magasin, rayon_9_2->nom_rayon);

    if (check == 2)
        printf("\nLes rayons ont bien été fusionnés.");
    else
        printf("\nErreur : Les rayons n'ont pas pu être fusionnés.");
}

/* *********************
 * Fonctions utilitaires
 ********************* */

// Vider le buffer (utile quand on utilise des getchar() )
void viderBuffer() {
    int c = 0;
    while (c != '\n' && c != EOF) {
        c = getchar();
    }
}

// Permet de chercher un rayon par son nom
T_Rayon* chercher_rayon_par_nom(T_Magasin *magasin, char *nom) {
    T_Rayon *rayon = magasin->liste_rayons;
    while (rayon != NULL && strcmp(rayon->nom_rayon, nom) != 0) {
        rayon = rayon->suivant;
    }
    return rayon;
}

// Fonction supplémentaire pour rendre le code plus clair.
int nombre_produits(T_Rayon *rayon) {
    int nb_produits = 0;
    T_Produit *produit = rayon->liste_produits;

    while (produit != NULL) {
        nb_produits++;
        // nb_produits += produit->quantite_en_stock;
        produit = produit->suivant;
    }

    return nb_produits;
}

// Ajoute un produit à la fin d'un rayon
int ajouter_produit_fin(T_Rayon *rayon, T_Produit *produit) {

    T_Produit *produit_a_ajouter = creerProduit(produit->designation, produit->prix, produit->quantite_en_stock);

    if (produit_a_ajouter == NULL)
        return 0; // erreur malloc

    if (rayon->liste_produits == NULL) {
        rayon->liste_produits = produit_a_ajouter;
        return 1;
    }

    T_Produit *produit_actuel = rayon->liste_produits;

    while (produit_actuel->suivant != NULL) {
        produit_actuel = produit_actuel->suivant;
    }

    produit_actuel->suivant = produit_a_ajouter;

    return 1;
}

T_Produit_Recherche* creer_produit_recherche(T_Produit *produit, char* nom_rayon) {
    T_Produit_Recherche *produit_recherche = malloc(sizeof(T_Produit_Recherche));

    if (produit_recherche == NULL) {
        // Erreur malloc
        return NULL;
    }

    produit_recherche->produit = produit;
    produit_recherche->nom_rayon = nom_rayon;

    return produit_recherche;
}

// Ajouter un produit à la liste des produits recherchés
int ajouter_produit_recherche(T_Produit_Recherche *produit_recherche, T_Produit *produit, char* nom_rayon) {

    T_Produit_Recherche *produit_a_ajouter = creer_produit_recherche(produit, nom_rayon);

    if (produit_a_ajouter == NULL) {
        // Erreur malloc
        return 0;
    }

    T_Produit_Recherche *produit_actuel = produit_recherche;
    T_Produit_Recherche *produit_precedent = NULL;

    while (produit_actuel != NULL && produit_actuel->produit->prix < produit->prix) {
        produit_precedent = produit_actuel;
        produit_actuel = produit_actuel->suivant;
    }

    if (produit_precedent == NULL) {
        // Le produit doit être ajouté en tête de liste
        produit_a_ajouter->suivant = produit_recherche;
        produit_recherche = produit_a_ajouter;
        return 1;
    }

    produit_precedent->suivant = produit_a_ajouter;

    produit_a_ajouter->suivant = produit_actuel;

    return 1;

}
