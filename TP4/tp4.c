// NF16 - TP 4 : Les Arbres Binaires de Recherche
// Auteurs : Soulaymane KEBLI et Mohamed TAHIRI
// Fichier de définition des fonctions

#include "tp4.h"


// Fonctions de base de l'énoncé

// Ajouter une position à une liste de positions
// O(listeP->nbPositions)
T_Position* ajouterPosition(T_Position* listeP, int ligne, int ordre, int numeroPhrase) {

    T_Position* p = creerPosition(ligne, ordre, numeroPhrase);

    // On ajoute la position en triant par numéro de ligne puis par ordre

    // On pointe sur l'élément précédent et l'élément courant
    T_Position* prec = NULL;
    T_Position* cour = listeP;

    // On se place au premier élément qui a un numéro de ligne
    // supérieur ou égal à celui de la position à ajouter
    while (cour != NULL && cour->numeroLigne < ligne) {
        prec = cour;
        cour = cour->suivant;
    }

    // Si on a des élements dans la ligne qui nous intéresse,
    // on se place à l'élement qui a un ordre
    // supérieur ou égal à celui de la position à ajouter
    while (cour != NULL && cour->numeroLigne == ligne && cour->ordre < ordre) {
        prec = cour;
        cour = cour->suivant;
    }

    if (cour != NULL && cour->numeroLigne == ligne && cour->ordre == ordre) {
        // On a trouvé une position identique
        // On n'ajoute rien et on libère la position
        free(p);
        return listeP;
    }

    // L'élément précédent est NULL = on est au début de la liste
    if (prec == NULL) {
        p->suivant = listeP;
        return p;
    }
    // Sinon, on place notre élément entre l'élément précédent et l'élément courant
    else {
        prec->suivant = p;
        p->suivant = cour;
        return listeP;
    }
}

// Ajouter une occurrence d'un mot à l'index
// O(h), h (hauteur de l'ABR) = log2(index->nbMotsDistincts)
int ajouterOccurrence(T_Index *index, char *mot, int ligne, int ordre, int phrase) {

    // On vérifie que le mot est bien composé de lettres
    if (!estLettres(mot))
        return 0;

    // On transforme le mot en minuscules
    minuscules(mot);

    T_Noeud* prec = NULL;
    T_Noeud* cour = index->racine;

    index->nbMotsTotal++;

    while (cour != NULL) {
        // Si le mot est déjà dans l'index, on ajoute la position à la liste
        if (strcmp(cour->mot, mot) == 0) {
            cour->nbOccurrences++;
            cour->listePositions = ajouterPosition(cour->listePositions, ligne, ordre, phrase);
            return 1;
        }
        // Sinon, on se place sur le fils gauche ou le fils droit
        else {
            prec = cour;
            // Si le mot est avant le mot du noeud courant dans l'ordre alphabétique
            if (strcmp(cour->mot, mot) > 0) {
                cour = cour->filsGauche;
            }
            // Sinon
            else {
                cour = cour->filsDroit;
            }
        }
    }

    // Si on arrive ici, le mot n'est pas dans l'index
    index->nbMotsDistincts++;
    // On crée un nouveau noeud et on l'ajoute à l'index
    T_Noeud* noeud = creerNoeud(mot);

    if (noeud == NULL)
        return 0;

    noeud->listePositions = ajouterPosition(noeud->listePositions, ligne, ordre, phrase);

    // Si l'index est vide, on place le noeud à la racine
    if (prec == NULL) {
        index->racine = noeud;
    }
    // Sinon, on place le noeud à gauche ou à droite du noeud précédent
    else {
        if (strcmp(prec->mot, mot) > 0) {
            prec->filsGauche = noeud;
        }
        else {
            prec->filsDroit = noeud;
        }
    }

    return 1;
}

// Indexer un fichier
// O(n * h), n = nombre de mots du fichier, h (hauteur de l'ABR) = log2(index->nbMotsDistincts)
int indexerFichier(T_Index *index, char *filename) {

    // On ouvre le fichier en lecture
    FILE *fichier = fopen(filename, "r");

    // Si le fichier n'existe pas, on renvoie 0
    if (fichier == NULL)
        return 0;

    char *texte = (char*) malloc(sizeof(char) * CARACTERES_MAX);
    if (texte == NULL) {
        printf("Erreur d'allocation mémoire");
        return 0;
    }

    // On lit le fichier caractère par caractère avec la fonction getc
    char c;
    int i = 0;
    // EOF = End Of File
    while ((c = fgetc(fichier)) != EOF) {
        texte[i] = c;
        i++;
    }

    // On ajoute le caractère de fin de chaîne
    texte[i] = '\0';

    // On ferme le fichier
    fclose(fichier);

    // On va stocker toutes les phrases dans une liste de chaînes de caractères
    char* listePhrases[PHRASES_MAX];

    // On découpe le texte en phrases avec strtok
    char *phrase_a_ajouter = strtok(texte, ".");

    // On parcourt la liste des phrases
    int j = 0;
    while (phrase_a_ajouter != NULL) {
        // On ajoute la phrase à la liste
        index->phrases[j] = (char*) malloc(sizeof(char) * strlen(phrase_a_ajouter));
        strcpy(index->phrases[j], phrase_a_ajouter);
        listePhrases[j] = phrase_a_ajouter;
        phrase_a_ajouter = strtok(NULL, ".");
        j++;
    }

    // On stocke les phrases dans l'index
    index->nbPhrases = j;

    int numeroLigne = 1;
    int numeroPhrase = 0;

    int ordre = 0;

    // On parcourt la liste des phrases
    for (int k = 0; k < index->nbPhrases; k++) {
        numeroPhrase++;
        char* phrase = listePhrases[k];

        // On découpe la phrase en mots avec strtok
        char *mot = strtok(phrase, " ");
        while (mot != NULL) {
            ordre++;

            // Si le mot contient \n, on incrémente le numéro de ligne
            if (strchr(mot, '\n') != NULL) {
                // Partie avant le \n
                char* avant = partieAvant(mot);

                if (strlen(avant) > 0)
                    ajouterOccurrence(index, avant, numeroLigne, ordre, numeroPhrase);

                // Partie après le \n
                numeroLigne++;
                ordre = 1;
                char* apres = partieApres(mot);

                if (strlen(apres) > 0)
                    ajouterOccurrence(index, apres, numeroLigne, ordre, numeroPhrase);
            } else {
                ajouterOccurrence(index, mot, numeroLigne, ordre, numeroPhrase);
            }

            mot = strtok(NULL, " ");
        }
    }
    return 1;
}

// Afficher la liste des mots classés par ordre alphabétique.
// O(index->nbMotsTotal)
void afficherIndex(T_Index index) {

    if (index.racine == NULL) {
        printf(ROUGE "L'index est vide." RESET "\n");
        return;
    }

    // On créé une liste de noeuds
    T_Noeud *listeMots[MOTS_MAX];
    int nbMots = 0;

    // On remplit la liste de noeuds à l'aide de cette fonction récursive
    // qui parcourt tout l'ABR en infixe
    // ce qui permet que le tableau soit trié par ordre alphabétique
    remplirTableauNoeuds(index.racine, listeMots, &nbMots);

    // On fait l'affichage de tous les mots qu'on a trouvé
    // En mettant une majuscule si le mot commence par une nouvelle lettre
    printf(ROUGE "%c" RESET "\n", listeMots[0]->mot[0] - 32);

    for (int i = 1; i < nbMots; i++) {

        if (listeMots[i]->mot[0] != listeMots[i-1]->mot[0])
            printf(ROUGE "\n%c" RESET "\n", listeMots[i]->mot[0] - 32);

        afficherMot(listeMots[i]);
    }
}

// Rechercher un mot dans l'index
// O(h), h (hauteur de l'ABR) = log2(index->nbMotsDistincts)
T_Noeud* rechercherMot(T_Index index, char *mot) {
    // On parcourt l'ABR jusqu'à trouver le mot
    T_Noeud *cour = index.racine;
    while (cour != NULL) {
        // Si on a trouvé le mot, on renvoie le noeud
        if (strcmp(cour->mot, mot) == 0) {
            return cour;
        }
        // Si le mot est avant le mot du noeud courant dans l'ordre alphabétique
        else if (strcmp(cour->mot, mot) > 0) {
            cour = cour->filsGauche;
        }
        // Sinon
        else {
            cour = cour->filsDroit;
        }
    }

    // Si on arrive ici, le mot n'est pas dans l'index
    return NULL;
}

// Afficher toutes les phrases qui contiennent `mot`
// O(h + n),
// n = nombre d'occurrences du mot dans l'index,
// h (hauteur de l'ABR) = log2(index->nbMotsDistincts)
void afficherOccurrencesMot(T_Index index, char *mot) {
    // On recherche le mot dans l'index
    T_Noeud *noeud = rechercherMot(index, mot);

    // Si le mot n'est pas dans l'index, on affiche un message d'erreur
    if (noeud == NULL) {
        printf(ROUGE "Le mot \"%s\" n'est pas dans l'index." RESET "\n", mot);
        return;
    }

    char* cap_mot = capitaliser(mot);
    printf("Mot = " CYAN "\"%s\"" RESET "\n", cap_mot);
    free(cap_mot);

    printf("Occurrences = %d\n", noeud->nbOccurrences);

    T_Position* position = noeud->listePositions;

    while (position != NULL) {
        // On met la phrase dans le format voulu
        char* phrase = ajoutEspacePhrase(index.phrases[position->numeroPhrase - 1]);

        // On affiche la phrase
        printf("| Ligne %d, mot %d :", position->numeroLigne, position->ordre);

        // On affiche les phrases caractère par caractère pour éviter certaines difficultés
        for (int i = 0; i < strlen(phrase); i++) {
            if (phrase[i] != '\n')
                printf("%c", phrase[i]);
            // Cela nous permet de ne pas afficher les \n qui sont en début de phrase
            else if (phrase[i] == '\n' && i != 1)
                printf(" ");
        }

        printf(".\n");

        free(phrase);

        position = position->suivant;
    }
}

// Construire un texte à partir de son index
// O(index->nbMotsTotal^2)
void construireTexte(T_Index index, char *filename) {
    // On ouvre le fichier en écriture
    FILE *fichier = fopen(filename, "w");

    // Si le fichier ne peut pas être créé
    if (fichier == NULL) {
        printf(ROUGE "Erreur lors de la création du fichier." RESET "\n");
        return;
    }

    // On affiche le texte dans le terminal
    printf(VERT "Texte généré dans le fichier \"%s\" :" RESET "\n\n", filename);

    // On parcourt l'index en préfixe, car les mots les plus hauts seront sûrement les premiers entrés
    // donc on aura sûrement moins de déplacements de tête de lecture
    T_Mot *listeMots = creerMot(capitaliser(index.racine->mot), index.racine->listePositions->numeroLigne, index.racine->listePositions->ordre, index.racine->listePositions->numeroPhrase);
    remplirTableauMots(index.racine->filsGauche, listeMots);
    remplirTableauMots(index.racine->filsDroit, listeMots);

    while (listeMots->suivant != NULL) {
        // On écrit le mot dans le fichier
        printf(ITALIQUE "%s" RESET, listeMots->mot);

        fprintf(fichier, "%s", listeMots->mot);

        if (listeMots->suivant->numeroLigne != listeMots->numeroLigne) {
            if (listeMots->suivant->numeroPhrase != listeMots->numeroPhrase) {
                printf(".\n");
                fprintf(fichier, ".\n");
                listeMots->suivant->mot = capitaliser(listeMots->suivant->mot);
            } else {
                printf("\n");
                fprintf(fichier, "\n");
            }
        } else if (listeMots->suivant->numeroPhrase != listeMots->numeroPhrase) {
            printf(". ");
            fprintf(fichier, ". ");
            listeMots->suivant->mot = capitaliser(listeMots->suivant->mot);
        } else {
            printf(" ");
            fprintf(fichier, " ");
        }

        // On libère la mémoire
        T_Mot *tmp = listeMots;
        listeMots = listeMots->suivant;
        free(tmp->mot);
        free(tmp);
    }

    // On écrit le dernier mot
    printf("%s.\n", listeMots->mot);
    fprintf(fichier, "%s.\n", listeMots->mot);

    // On ferme le fichier
    fclose(fichier);

    // On récupère le chemin absolu du fichier
    char *path = realpath(filename, NULL);

    printf("\n" VERT "Le fichier \"%s\" a bien été créé." RESET "\n", path);
}



// Fonctions utilitaires ajoutées

// Vider le buffer
// O(n), n = nombre de caractères dans le buffer
void viderBuffer() {
    int c = 0;
    while (c != '\n' && c != EOF) {
        c = getchar();
    }
}

// Vérifier qu'une chaîne de caractères n'est composé que de lettres
// O(strlen(mot))
int estLettres(char *mot) {
    int i = 0;
    while (mot[i] != '\0') {
        if (mot[i] < 'a' || mot[i] > 'z') {
            if (mot[i] < 'A' || mot[i] > 'Z') {
                return 0;
            }
        }
        i++;
    }
    return 1;
}

// Transformer les lettres majuscules d'une chaîne de caractères en minuscules
// O(strlen(mot))
void minuscules(char *mot) {
    int i = 0;
    while (mot[i] != '\0') {
        if (mot[i] >= 'A' && mot[i] <= 'Z') {
            mot[i] = mot[i] + 32;
        }
        i++;
    }
}

// Copie la chaîne de caractères en ajoutant une majuscule au début
// O(strlen(mot))
char* capitaliser(char* mot) {
    char* maj_mot = (char*)malloc(sizeof(char) * (strlen(mot) + 1));

    if (maj_mot == NULL) {
        printf("Erreur d'allocation mémoire");
        exit(1);
    }

    strcpy(maj_mot, mot);

    maj_mot[0] = maj_mot[0] - 32;
    return maj_mot;
}

// Récupérer la partie d'un mot avant un saut de ligne
// O(strlen(mot))
char* partieAvant(char* mot) {
    char* nouveauMot = (char*)malloc(sizeof(char) * (strlen(mot) + 1));

    if (nouveauMot == NULL) {
        printf("Erreur d'allocation mémoire");
        exit(1);
    }

    // On cherche le saut de ligne
    int i = 0;
    while (mot[i] != '\n') {
        nouveauMot[i] = mot[i];
        i++;
    }

    // On ajoute le caractère de fin de chaîne à la place du saut de ligne
    nouveauMot[i] = '\0';
    return nouveauMot;
}

// Récupérer la partie d'un mot après un saut de ligne
// O(strlen(mot))
char* partieApres(char* mot) {
    char* nouveauMot = (char*)malloc(sizeof(char) * (strlen(mot) + 1));

    if (nouveauMot == NULL) {
        printf("Erreur d'allocation mémoire");
        exit(1);
    }

    // On cherche le saut de ligne
    int i = 0;
    while (mot[i] != '\n') {
        i++;
    }
    i++;

    // On copie le reste du mot
    int j = 0;
    while (mot[i] != '\0') {
        nouveauMot[j] = mot[i];
        i++;
        j++;
    }

    nouveauMot[j] = '\0';
    return nouveauMot;
}

// Ajouter un espace si nécessaire et on colorie le mot.
// O(strlen(phrase))
char* ajoutEspacePhrase(char* phrase) {
    // On prévoit de l'espace pour ajouter un espace
    char* nouvellePhrase = (char*) malloc(sizeof(char) * strlen(phrase) + 2);

    if (nouvellePhrase == NULL) {
        printf("Erreur d'allocation mémoire");
        exit(1);
    }

    if (phrase[0] != ' ')
        sprintf(nouvellePhrase, " %s", phrase);
    else
        strcpy(nouvellePhrase, phrase);

    return nouvellePhrase;
}

// Créer un objet Position
// O(1)
T_Position* creerPosition(int numeroLigne, int ordre, int numeroPhrase) {
    T_Position* p = (T_Position*)malloc(sizeof(T_Position));

    if (p == NULL) {
        printf("Erreur d'allocation mémoire");
        exit(1);
    }

    p->numeroLigne = numeroLigne;
    p->ordre = ordre;
    p->numeroPhrase = numeroPhrase;
    p->suivant = NULL;
    return p;
}

// Créer un objet Noeud
// O(strlen(mot))
T_Noeud* creerNoeud(char *mot) {
    T_Noeud* noeud = (T_Noeud*)malloc(sizeof(T_Noeud));

    if (noeud == NULL) {
        printf("Erreur d'allocation mémoire");
        exit(1);
    }

    noeud->mot = (char*)malloc(sizeof(char) * (strlen(mot) + 1));

    if (noeud->mot == NULL) {
        printf("Erreur d'allocation mémoire");
        exit(1);
    }

    strcpy(noeud->mot, mot);

    noeud->nbOccurrences = 1;

    noeud->listePositions = NULL;
    noeud->filsGauche = NULL;
    noeud->filsDroit = NULL;

    return noeud;
}

// Créer un objet Index
// O(1)
T_Index* creerIndex() {
    T_Index* index = (T_Index*)malloc(sizeof(T_Index));

    if (index == NULL) {
        printf("Erreur d'allocation mémoire");
        exit(1);
    }

    index->racine = NULL;
    index->nbMotsDistincts = 0;
    index->nbMotsTotal = 0;
    index->nbPhrases = 0;

    return index;
}

// Créer un objet T_Mot
// O(1)
T_Mot* creerMot(char* mot, int numeroLigne, int ordre, int numeroPhrase) {
    T_Mot *obj_mot = (T_Mot*) malloc(sizeof(T_Mot));

    if (obj_mot == NULL) {
        printf("Erreur d'allocation mémoire\n");
        exit(1);
    }

    char* nouveau_mot = (char*) malloc(sizeof(char) * (strlen(mot) + 1));
    strcpy(nouveau_mot, mot);

    obj_mot->mot = nouveau_mot;
    obj_mot->numeroLigne = numeroLigne;
    obj_mot->ordre = ordre;
    obj_mot->numeroPhrase = numeroPhrase;

    obj_mot->suivant = NULL;

    return obj_mot;
}

// Afficher le mot d'un noeud et toutes ses occurrences
// O(noeud->nbOccurrences)
void afficherMot(T_Noeud *noeud) {
    // On affiche le mot
    char* cap_mot = capitaliser(noeud->mot);
    printf("|-- " CYAN "%s" RESET "\n", cap_mot);
    free(cap_mot);

    // On affiche toutes ses occurrences
    T_Position *cour = noeud->listePositions;
    while (cour != NULL) {
        printf("|---- (l:%d, o:%d, p:%d)\n", cour->numeroLigne, cour->ordre, cour->numeroPhrase);
        cour = cour->suivant;
    }
    printf("|\n");
}

// Remplir un tableau avec les noeuds de l'index (parcours récursif infixe)
// Complexité totale en partant de l'index : O(index->nbMotsDistincts)
void remplirTableauNoeuds(T_Noeud* noeud, T_Noeud** listeMots, int* nbMots) {
    // Parcours infixe
    if (noeud != NULL) {
        remplirTableauNoeuds(noeud->filsGauche, listeMots, nbMots);
        // On ajoute le noeud à la liste
        // On incrémente le nombre de mots
        // On utilise un pointeur pour que la valeur de nbMots soit globalement changée.
        listeMots[*nbMots] = noeud;
        (*nbMots)++;
        remplirTableauNoeuds(noeud->filsDroit, listeMots, nbMots);
    }
}

// Ajouter un mot à une liste de mots triées en ligne puis en ordre
// O(n) avec n = nombre de mots dans la liste
void ajouterMot(T_Mot *listeMots, char* mot, int numeroLigne, int ordre, int numeroPhrase) {

    T_Mot *obj_mot = creerMot(mot, numeroLigne, ordre, numeroPhrase);

    // On se place au début de la liste
    T_Mot *prec = NULL;
    T_Mot *cour = listeMots;

    // On se place au bon endroit dans la liste (triée en ligne puis en ordre)
    while (cour != NULL && cour->numeroLigne < numeroLigne) {
        prec = cour;
        cour = cour->suivant;
    }
    while (cour != NULL && cour->numeroLigne == numeroLigne
           && cour->ordre < ordre) {
        prec = cour;
        cour = cour->suivant;
    }

    // L'élément précédent est NULL = on est au début de la liste
    if (prec == NULL) {
        obj_mot->suivant = listeMots;
    }
        // Sinon, on place notre élément entre l'élément précédent et l'élément courant
    else {
        prec->suivant = obj_mot;
        obj_mot->suivant = cour;
    }
}

// Remplir le tableau de mots (question 7)
// Complexité totale en partant de l'index : O(index->nbMotsTotal^2)
void remplirTableauMots(T_Noeud *noeud, T_Mot *listeMots) {
    // Parcours préfixe
    if (noeud != NULL) {
        T_Position *position = noeud->listePositions;
        while (position != NULL) {
            ajouterMot(listeMots, noeud->mot, position->numeroLigne, position->ordre, position->numeroPhrase);
            position = position->suivant;
        }
        remplirTableauMots(noeud->filsGauche, listeMots);
        remplirTableauMots(noeud->filsDroit, listeMots);
    }
}