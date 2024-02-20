#include <stdio.h>
#include <string.h>
#include "tp3.h"

int main()
{
    T_Magasin *mon_magasin = NULL;

    // ============= MENU UTILISATEUR =============
    char choix = '_';
    while (choix != '0') {
        printf("\n Faites votre choix : (chiffre)");
        printf("\n======================================");
        printf("\n1. Créer un magasin");
        printf("\n2. Ajouter un rayon au magasin");
        printf("\n3. Ajouter un produit dans un rayon");
        printf("\n4. Afficher les rayons du magasin");
        printf("\n5. Afficher les produits d'un rayon");
        printf("\n6. Supprimer un produit");
        printf("\n7. Supprimer un rayon");
        printf("\n8. Rechercher un produit par prix");
        printf("\n9. Fusionner deux rayons du magasin");
        printf("\n0. Quitter");
        printf("\n======================================");
        printf("\n   Votre choix ? : ");
        choix = (char)getchar();
        viderBuffer(); // supprimer de l'entrée standard le retour charriot et les éventuels caractères supplémentaires tapés par l'utilisateur

        char nom[S_MAX];

        switch (choix) {
            case '1' :
                printf("\nNom du magasin : ");
                scanf(" %[^\n]", nom);
                viderBuffer();

                mon_magasin = creerMagasin(nom);
                // Créer un magasin

                printf("\nLe magasin %s a été créé avec succès.", nom);

                break;

            case '2' :

                if (mon_magasin == NULL) {
                    printf("\nVous devez d'abord créer un magasin.");
                    break;
                }

                printf("\nNom du rayon : ");
                scanf(" %[^\n]", nom);
                viderBuffer();

                // Ajouter un rayon au magasin
                if (ajouterRayon(mon_magasin, nom))
                    printf("\nLe rayon '%s' a été ajouté au magasin.", nom);
                else
                    printf("\nErreur : Le rayon '%s' n'a pas pu être ajouté au magasin.", nom);

                break;

            case '3' :

                if (mon_magasin == NULL) {
                    printf("\nVous devez d'abord créer un magasin.");
                    break;
                }

                // Ajouter un produit dans un rayon

                // Si le magasin est vide, on ne peut pas ajouter de produit
                if (mon_magasin->liste_rayons == NULL) {
                    printf("\nLe magasin est vide.");
                    break;
                }

                printf("\nDans quel rayon voulez-vous ajouter un produit ?\n");
                afficherMagasin(mon_magasin);
                printf("\nVotre choix : ");
                scanf(" %[^\n]", nom);
                viderBuffer();

                T_Rayon* rayon_3 = chercher_rayon_par_nom(mon_magasin, nom);

                if (rayon_3 == NULL) {
                    printf("Le rayon '%s' n'existe pas.", nom);
                    break;
                }

                char designation[S_MAX];
                float prix;
                int quantite;

                printf("Désignation du produit : ");
                scanf(" %[^\n]", designation);
                viderBuffer();

                printf("Prix du produit : ");
                scanf("%f", &prix);
                viderBuffer();

                printf("Quantité du produit : ");
                scanf("%d", &quantite);
                viderBuffer();

                if (ajouterProduit(rayon_3, designation, prix, quantite))
                    printf("\nLe produit '%s' a bien été ajouté au rayon '%s'.", designation, nom);
                else
                    printf("\nErreur : Le produit '%s' n'a pas pu être ajouté au rayon '%s'.", designation, nom);

                break;

            case '4' :
                // Afficher les rayons du magasin
                printf("\n");
                afficherMagasin(mon_magasin);
                break;

            case '5' :

                if (mon_magasin == NULL) {
                    printf("\nVous devez d'abord créer un magasin.");
                    break;
                }

                if (mon_magasin->liste_rayons == NULL) {
                    printf("\nLe magasin est vide.");
                    break;
                }

                // Afficher les produits d'un rayon
                printf("\nDe quel rayon voulez-vous voir les produits ?\n");
                afficherMagasin(mon_magasin);
                printf("\nVotre choix : ");
                scanf(" %[^\n]", nom);
                viderBuffer();

                T_Rayon* rayon_5 = chercher_rayon_par_nom(mon_magasin, nom);

                if (rayon_5 == NULL) {
                    printf("Le rayon '%s' n'existe pas.", nom);
                    break;
                }

                afficherRayon(rayon_5);

                break;

            case '6' :

                if (mon_magasin == NULL) {
                    printf("\nVous devez d'abord créer un magasin.");
                    break;
                }

                // Supprimer un produit

                if (mon_magasin->liste_rayons == NULL) {
                    printf("\nLe magasin est vide.");
                    break;
                }

                printf("\nDe quel rayon voulez-vous supprimer un produit ?\n");
                afficherMagasin(mon_magasin);
                printf("\nVotre choix : ");
                scanf(" %[^\n]", nom);
                viderBuffer();

                T_Rayon* rayon_6 = chercher_rayon_par_nom(mon_magasin, nom);

                if (rayon_6 == NULL) {
                    printf("Le rayon '%s' n'existe pas.", nom);
                    break;
                }

                if (rayon_6->liste_produits == NULL) {
                    printf("\nLe rayon est vide.");
                    break;
                }

                printf("\nQuel produit voulez-vous supprimer ?\n");
                afficherRayon(rayon_6);
                printf("\nVotre choix : ");
                scanf(" %[^\n]", nom);
                viderBuffer();

                if (supprimerProduit(rayon_6, nom))
                    printf("\nLe produit '%s' a bien été supprimé du rayon '%s'.", nom, rayon_6->nom_rayon);
                else
                    printf("\nErreur : Le produit '%s' n'a pas pu être supprimé du rayon '%s'.", nom, rayon_6->nom_rayon);


                break;

            case '7' :

                if (mon_magasin == NULL) {
                    printf("\nVous devez d'abord créer un magasin.");
                    break;
                }

                // Supprimer un rayon

                if (mon_magasin->liste_rayons == NULL) {
                    printf("\nLe magasin est vide.");
                    break;
                }

                printf("\nQuel rayon voulez-vous supprimer ?\n");
                afficherMagasin(mon_magasin);
                printf("\nVotre choix : ");
                scanf(" %[^\n]", nom);
                viderBuffer();

                if (supprimerRayon(mon_magasin, nom))
                    printf("\nLe rayon '%s' a bien été supprimé du magasin.", nom);
                else
                    printf("\nErreur : Le rayon '%s' n'a pas pu être supprimé du magasin.", nom);

                break;

            case '8' :

                if (mon_magasin == NULL) {
                    printf("\nVous devez d'abord créer un magasin.");
                    break;
                }

                // Rechercher un produit par prix
                printf("\nQuel est le prix minimum ? ");
                float prix_min;
                scanf("%f", &prix_min);
                viderBuffer();

                printf("\nQuel est le prix maximum ? ");
                float prix_max;
                scanf("%f", &prix_max);
                viderBuffer();

                rechercheProduits(mon_magasin, prix_min, prix_max);

                break;

            case '9' :

                if (mon_magasin == NULL) {
                    printf("\nVous devez d'abord créer un magasin.");
                    break;
                }

                // Fusionner deux rayons du magasin
                fusionnerRayons(mon_magasin);
                break;

            case '0' :
                printf("\n------ Programme terminé ------\n");
                break;

            default :
                printf("\n\nErreur : votre choix n'est pas valide !");
        }
        printf("\n\n\n");
    }

    return 0;
}