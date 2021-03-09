#include "semantique_syntaxique.h"
#include "../analyseur_lexical/headers/lexical.h"
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
    "cas erreur","erreur doublons","erreur modification constante", "erreur identificateur non declare", "erreur identificateur du programme non autorise", "erreur declaration type" ,"erreur is or :","erreur dans incrementation","erreur dans decrementation"
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
        Sym_Suiv();
            AFFECTATION();
            Test_Symbole(PV_TOKEN, PV_ERR);
            break;
        case CALL_TOKEN:
        Sym_Suiv();
            APPEL_FONCTION();
            Test_Symbole(PV_TOKEN, PV_ERR);
            break;
        case RETURN_TOKEN:
        Sym_Suiv();
            RETURN();
            Test_Symbole(PV_TOKEN, PV_ERR);
            break;
        case FOR_TOKEN:
        Sym_Suiv();
            BOUCLE();
            break;
        case DO_TOKEN:
        Sym_Suiv();
            BOUCLE();
            break;
        case REPEAT_TOKEN:
        Sym_Suiv();
            BOUCLE();
            break;
        case WHILE_TOKEN:
        Sym_Suiv();
            BOUCLE();
            break;
    }
    if(isIO(SYM_COUR.CODE)){
        Sym_Suiv();
        INPUT_OUTPUT();
    }
    else{
        switch(SYM_COUR.CODE){
            case DEF_TOKEN:
            Sym_Suiv();
                FONCTION();
                break;
            case FUNCTION_TOKEN:
            Sym_Suiv();
                FONCTION();
                break;
            case IF_TOKEN:
            Sym_Suiv();
                CONTROLE();
                break;
            case SWITCH_TOKEN:
            Sym_Suiv();
                CONTROLE();
                break;
            case PO_TOKEN:
            Sym_Suiv();
                CONTROLE();
                break;
            case CONST_TOKEN:
            Sym_Suiv();
                VAR_DECLARATION();
                Test_Symbole(PV_TOKEN, PV_ERR);
                break;
            case LET_TOKEN:
            Sym_Suiv();
                VAR_DECLARATION();
                Test_Symbole(PV_TOKEN, PV_ERR);
                break;
        }
    }
}

void AFFECTATION(){
    Test_Symbole(ID_TOKEN,ID_ERR);
    Fid();
}
void Fid(){
    switch(SYM_COUR.CODE){
        case AFFECPASCAL_TOKEN:
        Sym_Suiv();
            EXPRESSION();
            Test_Symbole(PV_TOKEN, PV_ERR);
            break;
        case AFF_ERR:
        Sym_Suiv();
            EXPRESSION();
            Test_Symbole(PV_TOKEN, PV_ERR);
            break;
        case AFFECARROW_TOKEN:
        Sym_Suiv();
            EXPRESSION();
            Test_Symbole(PV_TOKEN, PV_ERR);
            break;
    }
}
//if begining of term 1 else 0
int isTermBeg(int TOKEN){
    if(TOKEN==PLUS_TOKEN || TOKEN==MINUS_TOKEN || TOKEN==ID_TOKEN || TOKEN==NUMBER_TOKEN || TOKEN==BOOL_TOKEN || TOKEN==BOOLEAN_TOKEN || TOKEN==NUM_TOKEN || TOKEN==CALL_TOKEN || TOKEN==STR_TOKEN || TOKEN==STRING_TOKEN ){
        return 1;
    }
    return 0;
}

void EXPRESSION(){
    if(isTermBeg(SYM_COUR.CODE)){
        Sym_Suiv();
        TERM();
        FTERM();
    }
    else{
        Sym_Suiv();
        Test_Symbole(PO_TOKEN,PO_ERR);
        EXPRESSION();
        Test_Symbole(PF_TOKEN,PF_ERR);
    }
}

void FTERM(){
    if(SYM_COUR.CODE==PLUS_TOKEN || SYM_COUR.CODE==MINUS_TOKEN){
        Sym_Suiv();
        EXPRESSION();
    }
}

//if begining of term 1 else 0
int isTermBeg2(int TOKEN){
    if(TOKEN==ID_TOKEN || TOKEN==NUMBER_TOKEN || TOKEN==BOOL_TOKEN || TOKEN==BOOLEAN_TOKEN || TOKEN==NUM_TOKEN || TOKEN==CALL_TOKEN || TOKEN==STR_TOKEN || TOKEN==STRING_TOKEN ){
        return 1;
    }
    return 0;
}
void TERM(){
    if(isTermBeg2(SYM_COUR.CODE)){
        Sym_Suiv();
        FACTEUR();
        FFACTEUR();
    }
    else if(SYM_COUR==PLUS_TOKEN || SYM_COUR==MINUS_TOKEN){
        Sym_Suiv();
        FACTEUR();
    }
    else{}
}
//if multip MULT_TOKEN else 0
int isMultp(int TOKEN){
    if(TOKEN==MULT_TOKEN || TOKEN==MULT1_TOKEN || TOKEN==DIV_TOKEN || TOKEN==DIV1_TOKEN || TOKEN==MOD_TOKEN || TOKEN==MOD1_TOKEN || TOKEN==MODULO_TOKEN){
        return MULT_TOKEN;
    }
    return 0;
}

void FFACTEUR(){
    if(isMultp(SYM_COUR.CODE)==MULT_TOKEN){
        Test_Symbole(isMultp(SYM_COUR.CODE),MULT_ERR);
        FACTEUR();
    }
    else{
        Sym_Suiv();
        if(SYM_COUR==INCREM_TOKEN){
            Test_Symbole(INCREM_TOKEN,INCREM_ERR);
        }
        else if(SYM_COUR==DECREM_TOKEN){
            Test_Symbole(DECREM_TOKEN,DECREM_ERR);
        }
    }
}

void FACTEUR(){
    if(SYM_COUR.CODE==ID_TOKEN || SYM_COUR.CODE==NUM_TOKEN || SYM_COUR.CODE==NUMBER_TOKEN || SYM_COUR.CODE==BOOLEAN_TOKEN || SYM_COUR.CODE==BOOL_TOKEN || SYM_COUR.CODE==STRING_TOKEN || SYM_COUR.CODE==STR_TOKEN ){
        Sym_Suiv();
    }
    else if(SYM_COUR.CODE==CALL_TOKEN){
        Sym_Suiv();
        APPEL_FONCTION();
    }
    else{
        printf("erreur dans un facteur\n");
    }
}

void APPEL_FONCTION(){
    Test_Symbole(CALL_TOKEN,CALL_ERR);
    Test_Symbole(ID_TOKEN,ID_ERR);
    Test_Symbole(PO_TOKEN,PO_ERR);
    APPEL_FONCTION_ARG();
}

void APPEL_FONCTION_ARG(){
    if(SYM_COUR.CODE==ID_TOKEN){
        Sym_Suiv();
        ARGUMENT();
        Test_Symbole(PF_TOKEN,PF_ERR);
    }
    else if(SYM_COUR.CODE==PF_TOKEN){
        Sym_Suiv();
    }
    else{
        printf("erreur dans une fonction\n");
    }
}

void ARGUMENT(){
    Test_Symbole(ID_TOKEN,ID_ERR);
    ARGUMENT1();
}

void ARGUMENT1(){
    if(SYM_COUR.CODE==VIR_TOKEN){
        Sym_Suiv();
        ARGUMENT1();
    }
    else{}
}

void RETURN(){
    Test_Symbole(RETURN_TOKEN,RETURN_ERR);
    EXPRESSION();
}

void BOUCLE(){
    switch(SYM_COUR.CODE){
        case FOR_TOKEN:
            Sym_Suiv();
            FORLOOP_STATEMENT();
            break;
        case DO_TOKEN:
            Sym_Suiv();
            DOWHILELOOP_STATEMENT
            break;
       case REPEAT_TOKEN:
            Sym_Suiv();
            DOWHILELOOP_STATEMENT
            break;
        case WHILE_TOKEN:
            Sym_Suiv();
            WHILELOOP_STATEMENT();
            break;
    }
}

void FORLOOP_STATEMENT(){
    Test_Symbole(FOR_TOKEN,FOR_ERR);
    Ffor();
}

void Ffor(){
    if(SYM_COUR.CODE==PO_TOKEN){
        Sym_Suiv();
        FOR1();
    }
    else if(SYM_COUR.CODE==ID_TOKEN){
        Sym_Suiv();
        Fid3();
    }
    else{
        printf("erreur boucle for\n");
    }
}

==============


void FONCTION(){
    if(SYM_COUR.CODE==DEF_TOKEN||SYM_COUR.CODE==FUNCTION_TOKEN){
        sym_suiv();
        if(SYM_COUR.CODE==INT_TOKEN||
            SYM_COUR.CODE== INTEGER_TOKEN||
            SYM_COUR.CODE== NUMBER_TOKEN||
            SYM_COUR.CODE== FLOAT_TOKEN||
            SYM_COUR.CODE== CHAR_TOKEN||
            SYM_COUR.CODE== STRING_TOKEN||
            SYM_COUR.CODE== STR_TOKEN||
            SYM_COUR.CODE== LONG_TOKEN||
            SYM_COUR.CODE== DOUBLE_TOKEN||
            SYM_COUR.CODE== SHORT_TOKEN||
            SYM_COUR.CODE==UNSIGNED_TOKEN||
            SYM_COUR.CODE== BOOLEAN_TOKEN||
            SYM_COUR.CODE== BOOL_TOKEN||
            SYM_COUR.CODE== LET_TOKEN||
            SYM_COUR.CODE== $_TOKEN||
            SYM_COUR.CODE== BYTE_TOKEN||
            SYM_COUR.CODE== AUTO_TOKEN||SYM_COUR.CODE== VOID_TOKEN){
            sym_suiv();
            FONCTION2(); 
        }
    }
}

void FONCTION2(){
    if(SYM_COUR.CODE==ID_TOKEN){
        sym_suiv();
        Test_Symbole(PO_TOKEN, "parenthese ouvrante erreur");
        PARAMETER();
        Test_Symbole(PF_TOKEN, "parenthese fermante erreur");
        Test_Symbole(ACO_TOKEN, ACO_TOKEN);
        INSTRUCTIONS();
        Test_Symbole(ACF_TOKEN, ACF_TOKEN);
    }
}

void PARAMETER(){
    if(SYM_COUR.CODE==ID_TOKEN){
        sym_suiv();
        if(SYM_COUR.CODE==INT_TOKEN||
            SYM_COUR.CODE== INTEGER_TOKEN||
            SYM_COUR.CODE== NUMBER_TOKEN||
            SYM_COUR.CODE== FLOAT_TOKEN||
            SYM_COUR.CODE== CHAR_TOKEN||
            SYM_COUR.CODE== STRING_TOKEN||
            SYM_COUR.CODE== STR_TOKEN||
            SYM_COUR.CODE== LONG_TOKEN||
            SYM_COUR.CODE== DOUBLE_TOKEN||
            SYM_COUR.CODE== SHORT_TOKEN||
            SYM_COUR.CODE==UNSIGNED_TOKEN||
            SYM_COUR.CODE== BOOLEAN_TOKEN||
            SYM_COUR.CODE== BOOL_TOKEN||
            SYM_COUR.CODE== LET_TOKEN||
            SYM_COUR.CODE== $_TOKEN||
            SYM_COUR.CODE== BYTE_TOKEN||
            SYM_COUR.CODE== AUTO_TOKEN||SYM_COUR.CODE== VOID_TOKEN){
            PARAMETER1();
        }
    }
}

void PARAMETER1(){
    Test_Symbole(VIR_TOKEN, "virgule erreur");
    if(SYM_COUR.CODE==ID_TOKEN){
        sym_suiv();
        if(SYM_COUR.CODE==INT_TOKEN||
            SYM_COUR.CODE== INTEGER_TOKEN||
            SYM_COUR.CODE== NUMBER_TOKEN||
            SYM_COUR.CODE== FLOAT_TOKEN||
            SYM_COUR.CODE== CHAR_TOKEN||
            SYM_COUR.CODE== STRING_TOKEN||
            SYM_COUR.CODE== STR_TOKEN||
            SYM_COUR.CODE== LONG_TOKEN||
            SYM_COUR.CODE== DOUBLE_TOKEN||
            SYM_COUR.CODE== SHORT_TOKEN||
            SYM_COUR.CODE==UNSIGNED_TOKEN||
            SYM_COUR.CODE== BOOLEAN_TOKEN||
            SYM_COUR.CODE== BOOL_TOKEN||
            SYM_COUR.CODE== LET_TOKEN||
            SYM_COUR.CODE== $_TOKEN||
            SYM_COUR.CODE== BYTE_TOKEN||
            SYM_COUR.CODE== AUTO_TOKEN||SYM_COUR.CODE== VOID_TOKEN){
            PARAMETER1();
        }
    }
}
void CONTROLE (){
    switch(SYM_COUR.CODE){
        case IF_TOKEN : IF(); break;
        case CASE_TOKEN: CASE(); break;
        default : SHORTHAND(); break;
    }
}

void IF(){
    IF(); 
    FIF();
}

void FIF(){
    Test_Symbole(PO_TOKEN, "parenthese ouvrante erreur");
    FIF2();
}

void FIF2(){
    CONDITION(); 
    FCONDITION1();
}

void FCONDITION1() {
    Test_Symbole(PF_TOKEN, "parenthese fermante erreur");
    FCONDITION2();
}
void FCONDITION2(){
    BLOCK_IF(); 
    FBLOCK_IF();
}

void FBLOCK_IF(){
    if(SYM_COUR.CODE==ELSE_TOKEN){
        BLOCK_IF();
    }
    else {
        elIF(); 
        BLOCK_IF();    
        Test_Symbole(ELSE_TOKEN,"else erreur");
        BLOCK_IF();
        
}

void BLOCK_IF(){
    Test_Symbole(ACO_TOKEN, ACO_ERR);
    INSTRUCTIONS();
    Test_Symbole(ACF_TOKEN, ACF_ERR);
}

void CASE(){
    if(SYM_COUR.CODE==SWITCH_TOKEN){
        Test_Symbole(PO_TOKEN, "parenthese ouvrante erreur");
        EXPRESSION();
        Test_Symbole(PF_TOKEN, "parenthese fermante erreur");
        Test_Symbole(ACO_TOKEN, ACO_ERR);
        BLOCK_CASE();
        Test_Symbole(ACF_TOKEN, ACF_ERR);
    }
}

void BLOCK_CASE(){
    if(SYM_COUR.CODE==CASE_TOKEN){
        Fcase();
    }else if(SYM_COUR.CODE==CASE_TOKEN){
        Test_Symbole(PTS_TOKEN, "double points erreur");
        INSTRUCTIONS();
    }
}

void Fcase(){
    FACTEUR();
    FFACTEUR1();
}
void FFACTEUR1(){
    Test_Symbole(PTS_TOKEN, "double points erreur");
    FFACTEUR2();
}
void FFACTEUR2(){
    INSTRUCTIONS(); 
    FINSTRUCTIONS();
}
void FINSTRUCTIONS(){
    BLOCK_CASE();
}
void SHORTHAND(){
    Test_Symbole(PO_TOKEN, "parenthese ouvrante erreur");
    CONDITION();
    Test_Symbole(PF_TOKEN, "parenthese fermante erreur");
    Test_Symbole(INTERROGATION_TOKEN, "point d'interrogation erreur");
    INSTRUCTION();
    Test_Symbole(PTS_TOKEN, "double points erreur");
    INSTRUCTION();
}
void VAR_DECLARATION(){
    switch (SYM_COUR.CODE){
        case CONST_TOKEN:
            TYPE();
            IDS_CONST();
            break;
        case LET_TOKEN: 
            VARS2();
            break;
    }
}
void VARS2(){
    if(SYM_COUR.CODE==ID_TOKEN){
        Fid1();
    }
}
void Fid1(){
    VARS_TYPE();
    FVARS_TYPE();
}
void FVARS_TYPE(){
    switch (SYM_COUR.CODE){
        case AFFECT_TOKEN : Fsymbole_aff1(); break;
        case VIR_TOKEN : VARS2(); break;
        default: ; break;
    }
}
void Fsymbole_aff1(){
    EXPRESSION(); 
    FEXPRESSION();
}

void FEXPRESSION(){
    switch (SYM_COUR.CODE){
        case VIR_TOKEN : VARS2(); break;
        default: ; break;
    }
}
void VARS_TYPE(){
    if(SYM_COUR.CODE==PTS_TOKEN|SYM_COUR.CODE==IS_TOKEN)
        if(SYM_COUR.CODE==INT_TOKEN||
            SYM_COUR.CODE== INTEGER_TOKEN||
            SYM_COUR.CODE== NUMBER_TOKEN||
            SYM_COUR.CODE== FLOAT_TOKEN||
            SYM_COUR.CODE== CHAR_TOKEN||
            SYM_COUR.CODE== STRING_TOKEN||
            SYM_COUR.CODE== STR_TOKEN||
            SYM_COUR.CODE== LONG_TOKEN||
            SYM_COUR.CODE== DOUBLE_TOKEN||
            SYM_COUR.CODE== SHORT_TOKEN||
            SYM_COUR.CODE==UNSIGNED_TOKEN||
            SYM_COUR.CODE== BOOLEAN_TOKEN||
            SYM_COUR.CODE== BOOL_TOKEN||
            SYM_COUR.CODE== LET_TOKEN||
            SYM_COUR.CODE== $_TOKEN||
            SYM_COUR.CODE== BYTE_TOKEN||
            SYM_COUR.CODE== AUTO_TOKEN||SYM_COUR.CODE== VOID_TOKEN){
        
        }
}

void IDS_CONST(){
    Test_Symbole(ID_TOKEN,"identificateur erreur");
    Fid2();
}

void Fid2(){
    Test_Symbole(AFFECT_TOKEN, "affectation erreur");
    Fsymbole_aff();
}

void Fsymbole_aff(){
    EXPRESSION();
    FEXPRESSION();
}

void FEXPRESSION(){
    switch (SYM_COUR.CODE){
        case VIR_TOKEN : IDS_CONST(); break;
        default : break;
    }
}


void ERREUR(ERREURS e)
{
    good = false;
   printf("%s\n",ERR[e]);
}
