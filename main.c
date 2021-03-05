#include <stdio.h>
#include <stdlib.h>
#include "lexical.h"


int main()
{
    ouvrir_fichier("source.txt");
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






