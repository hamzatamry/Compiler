#include <stdio.h>
#include <stdlib.h>
#include "semantique_syntaxique.h"



int main()
{
    ouvrir_fichier("../lex.txt");
    Sym_Suiv();
    PROGRAM();
    if (good)                                             // variale globale indiquant si l'analyseur syntaxique valide ou pas le fichier
        printf("BRAVO: le programme est correcte!!!");
    else 
        printf("PAS BRAVO: fin de programme erronee!!!!");
    return 0;
}