#include "semantique_syntaxique.h"

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


FILE *f;

int current_size = 0;

bool good = true;

char ERR[][100] = {"erreur program","erreur constante", "erreur variable","erreur begin","End Erreur", "if erreur", "then erreur","While erreur",
"Do erreur","Erreur READ","WRITE erreur","Point virgule erreur","point erreur","double points erreur","plus erreur","monis erreur","multiplication erreur",
"division erreur", "virgule erreur", "egale erreur", "affectation erreur", "inferieur erreur", "inferieur ou egale erreur", "superieur erreur", "superieur ou egale erreur",
"different erreur","parenthese ouvrante erreur", "parenthese fermante erreur", "debut commentaire erreur", "fin commentaire erreur", "accolade ouvrante erreur",
"accolade fermante erreur", "fin de fichier erreur", "identificateur erreur", "numero erreur","else erreur", "until erreur", "repeat erreur", "for erreur",
"downto erreur", "case erreur", "of erreur", "into erreur", "erreur debut programme", "instruction erreur", "facteur erreur", "pour erreur", "fichier vide",
"cas erreur","erreur doublons","erreur modification constante", "erreur identificateur non declare", "erreur identificateur du programme non autorise"};


void ouvrir_fichier(char nom[20])
{
    f = fopen(nom,"r");
    if(f == NULL)
        printf("erreur ouverture fichier");

}

void Sym_Suiv()
{
    char c;
    int i = 0;
    strcpy(previous,SYM_COUR.NOM);
    while((c = fgetc(f)) != ' ')
    {
        SYM_COUR.NOM[i] = c;
        i++;
    }
    SYM_COUR.NOM[i] = '\0';
    fscanf(f,"%d", &(SYM_COUR.CODE));
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

};
void INSTRUCTIONS(){
  
};
void INSTRUCTION(){

};
void INST1(){

};
void ACC_O(){

};
void ACC_F(){

};
void AFFECTATION(){

};
void APPEL_FONCTION(){

};
void BOUCLE(){

};
void RETURN(){

};
void VAR_DECLARATION(){

};
void FONCTION(){

};
void CONTROLE(){

};
void EXCEPTION(){

};
void FILEHANDLING(){

};
void AFFECTATION1(){

};
void SYMBOLE_AFF(){

};
void ID(){

};
void EXPRESSION(){

};
void EG(){

};
void TERM(){

};
void EX1(){

};
void OPPERATEURADD(){

};
void VARS1(){

};
void TYPE(){

};
void IDS_CONST(){

};
void JS_IDS(){

};
void VARS2(){

};
void VARS_TYPE(){

};
void OPT(){

};
void VARS3(){

};
void IDS(){

};
void IDS1(){

};
void JS1(){

};
void IDS2(){

};
void IF_STMT(){

};
void COND(){

};
void IF_STMT_SYMB(){

};
void SUITE1(){

};
void END(){

};
void SWITCH(){

};
void SWITCH_IF(){

};
void STATEMENT(){

};
void SUITE_IF(){

};
void ELIF_STMT(){

};
void ELSE_BLOCK(){

};
void ELIF_SUITE(){

};
void SHORTHAND(){

};
void DOWHILELOOP_STATEMENT(){

};
void STATEMENTS(){

};
void CONDITION(){

};
void FORLOOP_STATEMENT(){

};
void A_F(){

};
void B_F(){

};
void AF1(){

};
void NOMBRE(){

};
void B_F1(){

};
void WHILELOOP_STATEMENT(){

};
void A_W(){

};
void B_W(){

};
void PARAMETERS(){

};
void FONCTION1(){

};
void PARAMETER(){

};
void OPPERATEURSPECIAUX(){

};
void COMPAR(){

};
void OPPERATEURMULT(){

};
void STRING(){

};









void ERREUR(ERREURS e)
{
    good = false;
   printf("%s\n",ERR[e]);
}

void addID(TSYM type)
{
    for(int i = 0; i < current_size; i++)
    {
        if(strcmp(previous,TAB_IDFS[i].NOM) == 0)
        {
            ERREUR(DOUBLONS_ERR);
            return;
        }
    }
    strcpy(TAB_IDFS[current_size].NOM,previous);
    TAB_IDFS[current_size].TIDF = type;
    current_size++;
}

void semCheck(int accepted)
{
    for(int i = 0; i < current_size; i++)
    {
        if(strcmp(TAB_IDFS[i].NOM,previous) == 0)
        {
            if(TAB_IDFS[i].TIDF == TCONST && !accepted)
                ERREUR(CONST_MODIF_ERR);
            else if(TAB_IDFS[i].TIDF == TPROG)
                ERREUR(PRO_ID_ERR);
            return;
        }
    }
    ERREUR(UNDECLARED_ERR);
}
