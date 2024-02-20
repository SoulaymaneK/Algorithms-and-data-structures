#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*
 Exercice 1
 */
void sommeRéel()
{
    float a,b;
    printf("Réel 1 : ");
    scanf("%f",&a);
    printf("\nRéel 2 : ");
    scanf("%f",&b);

    printf("Les deux réels sont %.2f et %.2f et leur somme est %.2f", a, b, a+b);
}

void permute()
{
    int a,b;
    printf("Valeur 1 : ");
    scanf("%d",&a);
    printf("\nValeur 2 : ");
    scanf("%d",&b);

    printf("\nV1 : %d et V2 : %d", a, b);
    printf("\n----Permutation----");
    int x = a;
    a = b;
    b = x;

    printf("\nV1 : %d et V2 : %d", a,b);
}

void pourcentage()
{
    float x,y;
    printf("Nombre : ");
    scanf("%f",&x);
    printf("\nPourcentage en %%: ");
    scanf("%f",&y);

    printf("%.1f%% de %.1f équivaut à %.1f.", y, x, y*x/100);
}

void temperature()
{
    float f;
    printf("Température en Fahrenheit : ");
    scanf("%f",&f);
    printf("Température en Celsius : %.2f°C",(f-32)*5/9);
}

void dec_oct_hex()
{
    int n;
    printf("Entier : ");
    scanf("%d",&n);
    printf("En décimal : %.2f\nEn octal : %o\nEn héxadécimal : %x", (float)n,n,n);
}

void pair_impair()
{
    int n;
    printf("Entier : ");
    scanf("%d",&n);
    if (n==0)
    {
        printf("L'entier est égal à 0.");
    }
    else if (n%2==0)
    {
        printf("L'entier est pair.");
    }
    else
    {
        printf("L'entier est impair.");
    }
}

void char_ascii()
{
    char car='5';
    car = (int)car;
    printf("%d", car);
}

/*
 Exercice 2
 */
void maj_int_min()
{
    char str;
    printf("Car : ");
    scanf("%c",&str);
    if (str>='A' && str<='Z')
        printf("Le caractère est compris entre 'A' et 'Z' --> c'est une Majuscule.");
    else if (str>='a' && str<='z')
        printf("Le caractère est compris entre 'a' et 'z' --> c'est une Minuscule.");
    else if (str>='0' && str<='9')
        printf("Le caractère est compris entre '0' et '9' --> c'est un Chiffre.");
    else
        printf("C'est un caractère spécial.");
}

void liste_entier()
{
    int n;
    int i = 1;
    do {
        printf("\nEntier %d : ",i);
        scanf("%d",&n);
        i++;
    } while (n!=-1 && n>0);
}

int affiche_table(int table);

void table_mult()
{
    int table;
    do {
        printf("\nQuelle table de multiplication voulez-vous, tapez 0 (zéro) pour sortir ? ");
        scanf("%d", &table);
        affiche_table(table);
    } while (table>0 && table<=9);
}

int affiche_table(int table)
{
    if (table>0 && table<=9)
    {
        for (int i = 0; i < 11; ++i) {
            printf("\n%d x %d = %d", table, i, table*i);
        }
    }
    else if (table==0)
    {
        printf("Fin du programme !");
        return 0;
    }
    else
    {
        printf("Ce n'est pas dans la possibilité du programme, recommencer !");
        return 0;
    }
}

void int_en_str()
{
    printf("Entrez un caractère : ");

    char c;

    c = getchar();

    switch (c)
    {
        case '1':
            printf("un");
            break;
        case '2':
            printf("deux");
            break;
        case '3':
            printf("trois");
            break;
        default:
            printf("autre caractère %c",c);
            break;
    }
}

/*
 * Exercice 3
 */

void tab_init()
{
    int tab[10][5];
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 5; ++j) {
            *(*(tab+i)+j) = 0;
        }
    }
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 5; ++j) {
            printf("%d\t",*(*(tab+i)+j));
        }
        printf("\n");
    }
}

void tab_init2()
{
    int tab[5] = {4,3,2,1,0};
}

void tab_init3()
{
    int tab[3][4];
    int count = 12;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 4 ; ++j) {
            tab[i][j] = count;
            // (*(tab+i))[j] = count; Pointeur sur la ligne
            // *(*(tab+i)+j) = count; Pointeur sur chaque case

            count++;
        }
    }
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 4 ; ++j) {
            printf("%d\t", tab[i][j]);
        }
        printf("\n");
    }
}

void mult_matrice()
{
    int M = 3, L = 2, N = 4;

    int matrice1[M][L], matrice2[L][N], produit[M][N];
    printf("Initialisation Matrice 1 de taille %dx%d",M,L);
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < L; ++j) {
            printf("\nEntier : ");
            scanf("%d",&matrice1[i][j]);
        }
    }
    printf("Initialisation Matrice 2 de taille %dx%d",L,N);
    for (int i = 0; i < L; ++i) {
        for (int j = 0; j < N; ++j) {
            printf("\nEntier : ");
            scanf("%d",&matrice2[i][j]);
        }
    }

    // Calculer le produit de matrices
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            produit[i][j] = 0;
            for (int k = 0; k < L; k++) {
                produit[i][j] += matrice1[i][k] * matrice2[k][j];
            }
        }
    }

    // Afficher la matrice résultat
    printf("Le produit de matrices est :\n");
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", produit[i][j]);
        }
        printf("\n");
    }
}

/*
 * Exercice 4
 */

void point()
{
    int i;
    int *j;
    i = 5;
    j = &i;
    printf("valeur de i = %d\nvaleur de j = %x\n",i,j);
    printf("adresse de i = %x\nadresse de j = %x\n",&i,&j);
    (*j)++;
    printf("i = %d après incrémentation de la donnée pointée par j\n",i);
    i*=5;
    printf("i = %d après multiplicaition de i par 5\n",*j);
    j++;
    printf("j = %x après incrémentation de j, valeur pointée par j : %d\n",j,*j);
}

void inverse_tab()
{
    //int n = 4;
    //int tab[] = {1,2,3,4,5};

    int n;
    printf("entrez le nombre de valeur que vous souhaité : ");
    scanf("%d",&n);
    int tab[n];
    for (int i = 0; i < n; ++i) {
        printf("valeur %d = ",i+1);
        scanf("%d",&tab[i]);
    }

    printf("\nsans decalage --> [");
    for (int i = 0; i < n-1; ++i) {
        printf("%d,",*(tab+i));
    }
    printf("%d]\n",*(tab+n-1));

    int temp = *tab;
    for (int i = 0; i <= n-1; ++i) {
        *(tab+i) = *(tab+i+1);
    }
    *(tab+n-1) = temp;

    printf("\ndecalage vers le haut --> [");
    for (int i = 0; i < n-1 ; ++i) {
        printf("%d,",*(tab+i));
    }
    printf("%d]\n",*(tab+n-1));

    temp = *(tab+n-1);
    for (int i = n-1; i >0; --i) {
        *(tab+i) = *(tab+i-1);
    }
    *tab = temp;

    printf("\ndecalage vers le bas --> [");
    for (int i = 0; i < n-1 ; ++i) {
        printf("%d,",*(tab+i));
    }
    printf("%d]\n",*(tab+n-1));
}

/*
 * Exercice 5
 */

int lire_ligne(char *chaine, size_t max)
{
    size_t i;
    for (i = 0; i < max - 1; ++i)
    {
        char c;

        if (scanf("%c", &c) != 1)
            return 0;
        else if (c == '\n')
            break;

        chaine[i] = c;
    }

    chaine[i] = '\0';
    return i;
}

void chaine_sousChaine() {

    char chaine[100], sous_chaine[100];
    int i, j, k, l, n = 0;

    printf("Entrez une chaine de caracteres : ");
    fgets(chaine, sizeof(chaine), stdin);

    printf("Entrez une sous-chaine de caracteres : ");
    fgets(sous_chaine, sizeof(sous_chaine), stdin);

    l = strlen(sous_chaine);

    printf("\n====================================================\n");
    for (i = 0; chaine[i] != '\0'; i++) {
        if (chaine[i] == sous_chaine[0]) {
            if (l-1 == 1)
            {
                printf("La sous-chaine se trouve a la position %d\n", i + 1);
                n++;
            }
            else
            {
                k = i + 1;
                for (j = 1; j < l && chaine[k] == sous_chaine[j]; j++, k++){
                    printf("La sous-chaine se trouve a la position %d\n", i + 1);
                    n++;
                }
            }
        }
    }
    printf("====================================================\n");
    printf("\n==> La sous-chaine se trouve %d fois dans la chaine\n", n);
}

void min_en_maj()
{
    char str[50];
    fgets(str, sizeof str, stdin);
    char new_str[255];
    for (size_t i = 0; i < sizeof str; ++i) {
        if (str[i] >= 'a' && str[i]<='z')
            new_str[i] = str[i] - ('a' - 'A');
        else
            new_str[i] = str[i];
    }
    printf("\n%s",new_str);
}

void pendu()
{
    char mot[30];
    printf("Entrez un mot : ");
    lire_ligne(mot,sizeof mot);
    char len_mot = strlen(mot);
    system("clear");
    char new_mot[30];
    int nbr_tentative = 0;

    for (size_t i = 0; i < len_mot && mot[i]!='\n'; ++i) {
        switch (*(mot+i)) {
            case ' ':
            case '-':
                *(new_mot+i) = *(mot+i);
                break;
            default:
                *(new_mot+i) ='*';
        }
    }
    printf("\n%s\n",new_mot);

    char c;

    while ((strcmp(mot,new_mot)!=0) && (nbr_tentative<10))
    {
        printf("\nun caractère : ");
        c = getchar();
        while (getchar() != '\n') ;
        for (size_t i = 0; i < len_mot; ++i)
        {
            if (c == *(mot+i))
            {
                *(new_mot+i) = c;
            }
        }
        printf("%s\n",new_mot);
        nbr_tentative ++;
        printf("Il vous reste %d tentatives !\n",10-nbr_tentative);
    }
    if (nbr_tentative==10)
        printf("\nVous avez utilisé toutes les tentatives possibles (%d), c'est PERDU !\n",nbr_tentative);
    else
        printf("\nVous avez GAGNE en %d tentatives !\n",nbr_tentative);
}