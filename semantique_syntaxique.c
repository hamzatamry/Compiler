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
"cas erreur","erreur doublons","erreur modification constante", "erreur identificateur non declare", "erreur identificateur du programme non autorise", "erreur declaration type" ,"erreur is or :"};


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
    if( SYM_COUR.CODE == CONST_TOKEN || SYM_COUR.CODE == LET_TOKEN || SYM_COUR.CODE == ID_TOKEN)
        VARS1();
    else 
        Test_Symbole(PV_TOKEN,PV_ERR);                // cas où VAR_DECLARATION == epsilon
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
    switch (SYM_COUR.CODE)
    {
    case CONST_TOKEN:
        Sym_Suiv();
        TYPE();             // ICI je pense c'est un terminal (make sure to call sym_suiv)
        IDS_CONST();
        break;
    case LET_TOKEN:
        Sym_Suiv();
        JS_IDS();
        break;
    case ID_TOKEN:
        VARS2();
        break;
    default:
        break;
    }
};

void TYPE(){
    switch(SYM_COUR.CODE){
        case INT_TOKEN:
            break;
        case INTEGER_TOKEN:
            break;
        case NUMBER_TOKEN:
            break;
        case FLOAT_TOKEN:
            break;
        case STR_TOKEN:
            break;
        case LONG_TOKEN:
            break;
        case DOUBLE_TOKEN:
            break;
        case SHORT_TOKEN:
            break;
        case UNSIGNED_TOKEN:               // ajouter les autres types apres ?
            break;
        case STRING_TOKEN:
            break;
        case CHAR_TOKEN:
            break;
        case BOOL_TOKEN:
            break;
        case BOOLEAN_TOKEN:
            break;
        default: 
            ERREUR(TYPE_ERR);
    }
    Sym_Suiv();                           // à verifier si jamais il'ya une erreur
};

void IDS_CONST(){
    Test_Symbole(ID_TOKEN,ID_ERR);
    AFFECTATION1();
    IDS1();
};

void JS_IDS(){
    Test_Symbole(ID_TOKEN,ID_ERR);
    Test_Symbole(PTS_TOKEN,PTS_ERR);
    TYPE();
    OPT();
    JS1();
};
void VARS2(){
    Sym_Suiv();
    Test_Symbole(ID_TOKEN,ID_ERR);
    VARS_TYPE();
    OPT();
    VARS3();
};
void VARS_TYPE(){
    switch (SYM_COUR.CODE)
    {
    case PTS_TOKEN:
        Sym_Suiv();
        TYPE();
        break;
    case IS_TOKEN:
         Sym_Suiv();
        TYPE();
        break;
    default:
        ERREUR(VARS_TYPE_ERR);
        break;
    }
};

void OPT(){
    if(SYM_COUR.CODE == PTS_TOKEN || SYM_COUR.CODE == EG_TOKEN || SYM_COUR.CODE == AFFECARROW_TOKEN)
        AFFECTATION1();
    else
    {
        switch (SYM_COUR.CODE)
        {
        case PTS_TOKEN:
            VARS3();
            break;
        case PV_TOKEN:                    
            JS1();
            break;
        default:
            return;
        }
      
    }
       
};
void VARS3(){
    if( SYM_COUR.CODE == VIR_TOKEN)
    {
        Sym_Suiv();
        VARS2();
    }
    else{
        Test_Symbole(PV_TOKEN,PV_ERR);              // check the followings of VARS3
        return;
    }
};

void IDS(){
    // Test_Symbole(ID_TOKEN,ID_ERR);
    // OPT();
    // IDS2();

    // à supprimer ?
};
void IDS1(){
    if (SYM_COUR.CODE == VIR_TOKEN)
    {
        Sym_Suiv();
        IDS_CONST();
    }
    else 
    {
        Test_Symbole(PV_TOKEN,PV_ERR);              // check the followings of IDS1
    }
};
void JS1(){
    if (SYM_COUR.CODE == VIR_TOKEN){
        Sym_Suiv();
        JS_IDS();
    }
    else{
        Test_Symbole(PV_TOKEN,PV_ERR);
        return;
    }
       
};
void IDS2(){
    // à supprimer ?
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
