#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "..\headers\syntaxique.h"

int main()
{
	printf("yo\n");
    ouvrir_fichier_syntaxique("tests\\input\\out_1");
    Sym_Suiv();
    PROGRAM();
    printf("here\n");
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