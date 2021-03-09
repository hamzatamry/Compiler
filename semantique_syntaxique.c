#include "semantique_syntaxique.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

FILE* lexical_output;
bool good = true;
char ERR[][100] = {
    "erreur program","erreur constante", "erreur variable","erreur begin","End Erreur", "if erreur", "then erreur","While erreur",
    "Do erreur","Erreur READ","WRITE erreur","Point virgule erreur","point erreur","double points erreur","plus erreur","monis erreur","multiplication erreur",
    "division erreur", "virgule erreur", "egale erreur", "affectation erreur", "inferieur erreur", "inferieur ou egale erreur", "superieur erreur", "superieur ou egale erreur",
    "different erreur","parenthese ouvrante erreur", "parenthese fermante erreur", "debut commentaire erreur", "fin commentaire erreur", "accolade ouvrante erreur",
    "accolade fermante erreur", "fin de fichier erreur", "identificateur erreur", "numero erreur","else erreur", "until erreur", "repeat erreur", "for erreur",
    "downto erreur", "case erreur", "of erreur", "into erreur", "erreur debut programme", "instruction erreur", "facteur erreur", "pour erreur", "fichier vide",
    "cas erreur","erreur doublons","erreur modification constante", "erreur identificateur non declare", "erreur identificateur du programme non autorise", "erreur declaration type" ,"erreur is or :"
};


void ouvrir_fichier(char nom[20])
{
    lexical_output = fopen(nom,"r");
    
    if (lexical_output == NULL) 
    {
        printf("erreur ouverture fichier");
        exit(-1);
    }

}

void Sym_Suiv()
{
    char c;
    int i = 0;

    while((c = fgetc(lexical_output)) != ' ')
    {
        SYM_COUR.NOM[i] = c;
        i++;
    }
    SYM_COUR.NOM[i] = '\0';
    fscanf(lexical_output,"%d", &(SYM_COUR.CODE));
}

void Test_Symbole(CODES_LEX lex,ERREURS err)
{
    if(SYM_COUR.CODE == lex)
    {
        Sym_Suiv();
    }

    else
        ERREUR(err);
}

void PROGRAM(){
    INSTRUCTIONS();
}

void INSTRUCTIONS(){
    if(SYM_COUR.CODE==ACO_TOKEN){
        Sym_Suiv();
        INSTRUCTION();
        INSTRUCTIONS();
        Test_Symbole(ACF_TOKEN, ACF_ERR);
    }
    else{
        INSTRUCTION();
        FINSTRUCTION();
    }
}
void FINSTRUCTION(){
    INSTRUCTIONS();
}

//if IO token 1 else 0;
int isIO(int TOKEN){
    if(TOKEN==PRINT_TOKEN || TOKEN==PRINTF_TOKEN || TOKEN==SCANF_TOKEN || TOKEN==INPUT_TOKEN || TOKEN==LOG_TOKEN || TOKEN==FPRINTF_TOKEN || TOKEN==FSCANF_TOKEN || TOKEN==FREAD_TOKEN || TOKEN==FWRITE_TOKEN || TOKEN==WRITE_TOKEN || TOKEN==READ || TOKEN==PUTS_TOKEN || TOKEN==GETS_TOKEN){
        return 1;
    }
    else{
        return 0;
    }
}

void INSTRUCTION(){
    switch(SYM_COUR.CODE){
        case ID_TOKEN: 
            AFFECTATION();
            Test_Symbole(ACF_TOKEN, ACF_ERR);
            break;
        case CALL_TOKEN:
            APPEL_FONCTION();
            Test_Symbole(ACF_TOKEN, ACF_ERR);
            break;
        case RETURN_TOKEN:
            RETURN();
            Test_Symbole(ACF_TOKEN, ACF_ERR);
            break;
        case FOR_TOKEN:
            BOUCLE();
            break;
        case DO_TOKEN:
            BOUCLE();
            break;
        case REPEAT_TOKEN:
            BOUCLE();
            break;
        case WHILE_TOKEN:
            BOUCLE();
            break;
    }
    if(isIO(SYM_COUR.CODE)){
        INPUT_OUTPUT();
    }
    else{
        switch(SYM_COUR.CODE){
            case DEF_TOKEN:
                FONCTION();
                break;
            case FUNCTION_TOKEN:
                FONCTION();
                break;
            case :
                CONTROLE();
                break;
            case :
                CONTROLE();
                break;
            case :
                CONTROLE();
                break;
            case :
                CONTROLE();
                break;
        }
    }
}

void ERREUR(ERREURS e)
{
    good = false;
   printf("%s\n",ERR[e]);
}