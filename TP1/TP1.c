#include "TP1.h"
void pendu_();

int main()
{
    pendu_();
    return 0;
}

void pendu_()
{
    char mot[30];
    printf("Entrez un mot : ");
    fgets(mot, sizeof mot, stdin);
    char len_mot = strlen(mot);
    system("clear");
    char new_mot[30];
    int nbr_tentative = 0;

    for (size_t i = 0; i <=len_mot && mot[i]!='\n'; ++i) {
        switch (*(mot+i)) {
            case ' ':
            case '-':
                *(new_mot+i) = *(mot+i);
                break;
            default:
                *(new_mot+i) ='*';
        }
    }
    printf("%d %d\n", strlen(mot), strlen(new_mot));
    printf("%c\n",*(new_mot+len_mot-1));
    *(new_mot+len_mot) = '\n';
    *(new_mot+len_mot+1) = '\0';
    printf("%d %d\n", strlen(mot), strlen(new_mot));
    printf("\n%s\n",new_mot);
   /* char c;

    while ((strcmp(mot,new_mot)!=0) && (nbr_tentative<10))
    {
        printf("\nIl vous reste %d tentatives !",10-nbr_tentative);
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
    }
    if (nbr_tentative==10)
        printf("\nVous avez utilisé toutes les tentatives possibles (%d), c'est PERDU !\n",nbr_tentative);
    else
        printf("\nVous avez GAGNE en %d tentatives !\n",nbr_tentative);*/
}