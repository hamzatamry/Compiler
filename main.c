#include <stdio.h>
#include <stdlib.h>
#include "lexical.h"


int main()
{
    ouvrir_fichier("source.c");
    while(Car_Cour != EOF)
    {
        sym_suiv();
        afficher_token();
    }
    printf("EOF -> EOF_TOKEN");
    fprintf(g,"EOF %d\n",EOF_TOKEN);     // g est le fichier d'entree de l'analyseur syntaxique
    return 0;
}






