// NF16 - TP 4 : Les Arbres Binaires de Recherche
// Auteurs : Soulaymane KEBLI et Mohamed TAHIRI
// Fichier principal, interface utilisateur

#include "tp4.h"

int main()
{
    T_Index* index = creerIndex();

    // indexerFichier(index, "texte.txt");

    if (index == NULL) {
        printf(ROUGE "Erreur : l'index n'a pas pu être créé !" RESET);
        return 0;
    }

    // ============= MENU UTILISATEUR =============
    char choix = '_';
    char mot[MAX_PAR_MOT];
    char cwd[1024];
    while (choix != '0') {
        printf("\n Faites votre choix : (chiffre)");
        printf("\n======================================");
        printf("\n1. Charger un fichier");
        printf("\n2. Caractéristiques de l'index");
        printf("\n3. Afficher l'index");
        printf("\n4. Rechercher un mot");
        printf("\n5. Afficher les occurrences d’un mot");
        printf("\n6. Construire le texte à partir de l’index");
        printf("\n7. Quitter");
        printf("\n======================================");
        printf("\n   Votre choix ? : ");
        choix = (char)getchar();
        viderBuffer();

        switch (choix) {

            case '1' :
                // Charger un fichier
                printf("\n------ Charger un fichier ------\n");

                // On informe l'utilisateur du répertoire courant
                // car en le lançant depuis un IDE ou depuis le terminal
                // le répertoire courant n'est parfois pas le même.
                if (getcwd(cwd, sizeof(cwd)) != NULL) {
                    printf(CYAN "!!! Répertoire courant : %s !!!\n" RESET, cwd);
                }

                printf("Entrez le nom du fichier à charger : ");
                char filename[100];
                scanf("%s", filename);
                viderBuffer();

                int resultat = indexerFichier(index, filename);

                if (resultat == 0) {
                    printf("\n" ROUGE "Erreur : le fichier \"%s\" n'a pas pu être chargé !" RESET, filename);
                } else {
                    printf("\n" VERT "Le fichier \"%s\" a bien été chargé !" RESET, filename);
                }

                break;

            case '2' :
                // Caractéristiques de l'index
                printf("\n------ Caractéristiques de l'index ------\n");

                if (index->racine == NULL) {
                    printf("\n" ROUGE "L'index est vide !" RESET);
                    break;
                }

                printf("Nombre de mots distincts : %d\n", index->nbMotsDistincts);
                printf("Nombre de mots total : %d\n", index->nbMotsTotal);
                printf("Nombre de phrases : %d", index->nbPhrases);

                break;

            case '3' :
                // Afficher l'index
                printf("\n------ Affichage de l'index ------\n");
                afficherIndex(*index);
                break;

            case '4' :
                // Rechercher un mot

                if (index->racine == NULL) {
                    printf(ROUGE "L'index est vide !" RESET);
                    break;
                }

                printf("\n------ Recherche d'un mot ------\n");
                printf("Entrez le mot à rechercher : ");
                scanf("%s", mot);
                minuscules(mot);
                viderBuffer();

                printf("\n");
                T_Noeud* noeud = rechercherMot(*index, mot);

                if (noeud == NULL) {
                    printf(ROUGE "Le mot n'a pas été trouvé !" RESET);
                    break;
                }

                afficherMot(noeud);

                break;

            case '5' :
                // Afficher les occurrences d’un mot
                if (index->racine == NULL) {
                    printf("\n" ROUGE "L'index est vide !" RESET);
                    break;
                }

                printf("\n------ Recherche d'un mot ------\n");
                printf("Entrez le mot à rechercher : ");
                scanf("%s", mot);
                minuscules(mot);
                viderBuffer();

                printf("\n");
                afficherOccurrencesMot(*index, mot);
                break;

            case '6' :
                // Construire le texte à partir de l’index
                if (index->racine == NULL) {
                    printf("\n" ROUGE "L'index est vide !" RESET );
                    break;
                }

                printf("\n------ Construction du texte ------\n");
                printf("Entrez le nom du fichier à construire : ");
                scanf("%s", filename);
                viderBuffer();

                construireTexte(*index, filename);

                break;

            case '7' :
                // Quitter
                printf("\n------ Programme terminé ------\n");
                return 1;

            default :
                // Choix invalide
                printf("\n" ROUGE "Erreur : votre choix n'est pas valide !" RESET);
        }
        printf("\n");
    }
    return 0;
}