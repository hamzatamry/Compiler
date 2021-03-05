#include <stdio.h>
#include <stdlib.h>
#include "headers/lexical.h"

int main()
{
    ouvrir_fichier("tests\\input\\in_1");
    while(Car_Cour != EOF)
    {
        sym_suiv();
        afficher_token();
    }
    printf("EOF -> EOF_TOKEN");
    fprintf(g,"EOF %d\n",EOF_TOKEN);     // g est le fichier d'entree de l'analyseur syntaxique
    fclose(g);
    fclose(f);
    return 0;
}






