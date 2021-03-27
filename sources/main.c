#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "..\headers\lexical.h"

int main(void)
{
    ouvrir_fichier("tests\\input\\in_3");

    while (Car_Cour != EOF)
    {
        sym_suiv();
        afficher_token();
    }
    printf("EOF -> EOF_TOKEN");
    fprintf(flux_output,"EOF %d\n",EOF_TOKEN);     // flux_output est le fichier d'entree de l'analyseur syntaxique
    fclose(flux_output);
    fclose(flux_input);
    return 0;
}






