#ifndef TP3_H_INCLUDED
#define TP3_H_INCLUDED

#define S_MAX 50

// Structures et types
struct Produit {
    char *designation;
    float prix;
    int quantite_en_stock;
    struct Produit *suivant;
};
typedef struct Produit T_Produit;

struct Rayon {
    char * nom_rayon;
    T_Produit *liste_produits;
    struct Rayon *suivant;
};

typedef struct Rayon T_Rayon;

struct Magasin {
    char *nom;
    T_Rayon *liste_rayons;
};
typedef struct Magasin T_Magasin;


// Création et initialisation des structures
T_Produit *creerProduit(char *designation, float prix, int quantite);
T_Rayon *creerRayon(char *nom);
T_Magasin *creerMagasin(char *nom);

// Ajout d'un rayon dans un magasin
int ajouterRayon(T_Magasin *magasin, char *nomRayon);

// Ajout d'un produit dans un rayon
int ajouterProduit(T_Rayon *rayon,char *designation, float prix, int quantite);

// Affichage de tous les rayons d'un magasin
void afficherMagasin(T_Magasin *magasin);

// Affichage de tous les produits d'un rayon
void afficherRayon(T_Rayon *rayon);

// Suppression d'un produit dans un rayon
int supprimerProduit(T_Rayon *rayon, char* designation_produit);

// Suppression d'un rayon et de tous les produits qu'il contient
int supprimerRayon(T_Magasin *magasin, char *nom_rayon);

// Recherche des produits se situant dans une fourchette de prix entrée par l'utilisateur
void rechercheProduits(T_Magasin *magasin, float prix_min, float prix_max);

// Trier une liste de produits dans un ordre croissant
void trierProduits(T_Produit** liste_produits, int nb_produits);

// Fusionner deux rayons
void fusionnerRayons(T_Magasin *magasin);


// UTILS
void viderBuffer();

// Recherche d'un rayon par son nom
T_Rayon* chercher_rayon_par_nom(T_Magasin *magasin, char *nom);

// Retourne le nombre de produits d'un rayon
int nombre_produits(T_Rayon *rayon);

// Ajoute un produit à la fin de la liste des produits d'un rayon
int ajouter_produit_fin(T_Rayon *rayon, T_Produit *produit);

// Permet la question 8.
struct Produit_Recherche {
    T_Produit *produit;
    char* nom_rayon;
    struct Produit_Recherche *suivant;
};
typedef struct Produit_Recherche T_Produit_Recherche;

// Créer un T_Produit_Recherche*
T_Produit_Recherche* creer_produit_recherche(T_Produit *produit, char* nom_rayon);

// Ajouter un produit à la liste des produits recherchés
int ajouter_produit_recherche(T_Produit_Recherche *produit_recherche, T_Produit *produit, char* nom_rayon);


#endif // TP3_H_INCLUDED