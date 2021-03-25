#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "..\headers\syntaxique.h"

int main()
{
    ouvrir_fichier_syntaxique("tests\\input\\out_3");
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