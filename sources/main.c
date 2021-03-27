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
        printf("\033[32mBRAVO: le programme est correcte!!!\033[0m");
    
    }                                     
    else 
    {
        printf("\033[31mPAS BRAVO: fin de programme erronee!!!!\033[0m");
    }
    return 0;
}