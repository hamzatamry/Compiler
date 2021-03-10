#include <stdio.h>
#include <stdlib.h>
#include "semantique_syntaxique.h"

int main()
{
	printf("yo\n");
    ouvrir_fichier("..\\analyseur_lexical\\tests\\output\\out_1");
    Sym_Suiv();
    PROGRAM();
    if (good)       
    {
        printf("BRAVO: le programme est correcte!!!");
    }                                     
    else 
    {
        printf("PAS BRAVO: fin de programme erronee!!!!");
    }
    return 0;
}