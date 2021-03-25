#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "..\headers\syntaxique.h"

FILE* lexical_output;
_Bool good = true;

void _log(int ligne)
{
    printf("%d SYM_COUR.NOM = %s SYM_COUR.CODE = %d\n", ligne,SYM_COUR.NOM, SYM_COUR.CODE);
}

void ouvrir_fichier_syntaxique(char nom[22])
{
    printf("%s",nom);
    lexical_output = fopen(nom,"r");
    
    if (lexical_output == NULL) 
    {
        printf("erreur ouverture fichier");
        exit(-1);
    }

}

void Sym_Suiv()
{
    fscanf(lexical_output,"%s", &(SYM_COUR.NOM));
    fscanf(lexical_output,"%d", &(SYM_COUR.CODE));
}

void Test_Symbole(CODES_LEX lex,ERREURS err)
{
    if(SYM_COUR.CODE == lex)
    {
        Sym_Suiv();
    }
    else
    {
        erreur_syntaxique(err);
        Sym_Suiv();
    }
        
}

void PROGRAM(){
    printf("debut\n");
    _log(50);
    INSTRUCTIONS();
}

void INSTRUCTIONS(){
    
    if(SYM_COUR.CODE==ACO_TOKEN){
        Sym_Suiv();
        _log(59);
        INSTRUCTION();
        INSTRUCTIONS();
        // Test_Symbole(ACF_TOKEN, ACF_ERR);
    }
    else if (SYM_COUR.CODE == ACF_TOKEN)
    {
        Sym_Suiv();
    }
    else{
        INSTRUCTION();
        FINSTRUCTION();
    }
}

void FINSTRUCTION(){
    if (SYM_COUR.CODE == EOF_TOKEN ||SYM_COUR.CODE == ACF_TOKEN)
    {
        _log(77);
        return;
    }
    INSTRUCTIONS();
}

//if IO token 1 else 0;
int isIO(int TOKEN){
    if(TOKEN==PRINT_TOKEN || TOKEN==PRINTF_TOKEN || TOKEN==SCANF_TOKEN || TOKEN==INPUT_TOKEN || TOKEN==LOG_TOKEN || TOKEN==FPRINTF_TOKEN || TOKEN==FSCANF_TOKEN || TOKEN==FREAD_TOKEN || TOKEN==FWRITE_TOKEN || TOKEN==WRITE_TOKEN || TOKEN==READ_TOKEN || TOKEN==PUTS_TOKEN || TOKEN==GETS_TOKEN){
        return 1;
    }
    else{
        return 0;
    }
}

void INSTRUCTION(){

    if(isIO(SYM_COUR.CODE) == 1){
        INPUT_OUTPUT();
    }
    switch(SYM_COUR.CODE){
        case ID_TOKEN: 
            AFFECTATION();
            Test_Symbole(PV_TOKEN, PV_ERR);
            break;
        case CALL_TOKEN:
            APPEL_FONCTION();
            Test_Symbole(PV_TOKEN, PV_ERR);
            break;
        case RETURN_TOKEN:
            RETURN();
            Test_Symbole(PV_TOKEN, PV_ERR);
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
        case DEF_TOKEN:
            FONCTION();
            break;
        case FUNCTION_TOKEN:
            FONCTION();
            break;
        case IF_TOKEN:
            CONTROLE();
            break;
        case SWITCH_TOKEN:
            CONTROLE();
            break;
        case PO_TOKEN:
            CONTROLE();
            break;
        case CONST_TOKEN:
            VAR_DECLARATION();
            Test_Symbole(PV_TOKEN, PV_ERR);
            break;
        case LET_TOKEN:
            VAR_DECLARATION();
            Test_Symbole(PV_TOKEN, PV_ERR);
            break;
        //default: good = false;
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
        case EG_TOKEN:
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
    if(TOKEN==PLUS_TOKEN || TOKEN==MINUS_TOKEN || TOKEN==ID_TOKEN || TOKEN==TRUE_TOKEN || TOKEN == FALSE_TOKEN || TOKEN==NUM_TOKEN|| TOKEN==CALL_TOKEN || TOKEN==STRINGVAL_TOKEN || TOKEN==CHAR_VALUE_TOKEN ){
        return 1;
    }
    return 0;
}

void EXPRESSION(){
    if(isTermBeg(SYM_COUR.CODE) == 1){
        TERM();
        FTERM();
    }
    else{
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
    if( TOKEN==ID_TOKEN || TOKEN==TRUE_TOKEN || TOKEN == FALSE_TOKEN || TOKEN==NUM_TOKEN|| TOKEN==CALL_TOKEN || TOKEN==STRINGVAL_TOKEN || TOKEN==CHAR_VALUE_TOKEN){
        return 1;
    }
    return 0;
}

void TERM(){
    if(isTermBeg2(SYM_COUR.CODE) == 1){
        FACTEUR();
        FFACTEUR();
    }
    else if(SYM_COUR.CODE==PLUS_TOKEN || SYM_COUR.CODE==MINUS_TOKEN){
        FACTEUR();
    }
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
        if(SYM_COUR.CODE==INCREM_TOKEN){
            Test_Symbole(INCREM_TOKEN,INCREM_ERR);
        }
        else if(SYM_COUR.CODE==DECREM_TOKEN){
            Test_Symbole(DECREM_TOKEN,DECREM_ERR);
        }
    }
}

void FACTEUR(){
    if(SYM_COUR.CODE==ID_TOKEN || SYM_COUR.CODE==TRUE_TOKEN || SYM_COUR.CODE == FALSE_TOKEN || SYM_COUR.CODE==NUM_TOKEN|| SYM_COUR.CODE==CALL_TOKEN || SYM_COUR.CODE==STRINGVAL_TOKEN || SYM_COUR.CODE == CHAR_VALUE_TOKEN ){
        Sym_Suiv();
    }
    else if(SYM_COUR.CODE==CALL_TOKEN){
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
        Test_Symbole(VIR_TOKEN,VIR_ERR);
        Test_Symbole(ID_TOKEN,ID_ERR);
        _log(280);
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
            FORLOOP_STATEMENT();
            break;
        case DO_TOKEN:
            DOWHILELOOP_STATEMENT();
            break;
       case REPEAT_TOKEN:
            DOWHILELOOP_STATEMENT();
            break;
        case WHILE_TOKEN:
            WHILELOOP_STATEMENT();
            break;
        default : 
        printf("boucle error\n");
    }
}

void FORLOOP_STATEMENT(){
    Test_Symbole(FOR_TOKEN,FOR_ERR);
    Ffor();
}

void Ffor(){
    if(SYM_COUR.CODE==PO_TOKEN){
        Test_Symbole(PO_TOKEN,PO_ERR);
        FOR1();
    }
    else if(SYM_COUR.CODE==ID_TOKEN){
        Test_Symbole(ID_TOKEN,ID_ERR);
        _log(316);
        Fid3();
    }
    else{
        printf("erreur boucle for\n");
    }
}

void FOR1(){
    VAR_DECLARATION();
    FVAR_DECLARATION();

}

void FVAR_DECLARATION(){
    switch(SYM_COUR.CODE){
        case PV_TOKEN:
            FVAR_DECLARATION2();
            break;
        case PTS_TOKEN :
            FVAR_DECLARATION3();
            break;
        default: 
            erreur_syntaxique(TYPE_ERR);          // ?
    }

}

void FVAR_DECLARATION2(){
    CONDITIONS();
    FCONDITIONS1();
}

void FCONDITIONS1(){
    Test_Symbole(PV_TOKEN,PV_ERR);
    FCONDITIONS2();

}

void FCONDITIONS2(){
    INSTRUCTION();
    FINSTRUCTION1();
}

void FINSTRUCTION1(){
    Test_Symbole(PF_TOKEN,PF_ERR);
    FINSTRUCTION2();
}

void FINSTRUCTION2(){
    if(SYM_COUR.CODE == ACO_TOKEN){
        Sym_Suiv();
        INSTRUCTIONS();
        Test_Symbole(ACF_TOKEN,ACF_ERR); 
    }
    else{
        INSTRUCTION();
    }
}

void FVAR_DECLARATION3(){
    Test_Symbole(ID_TOKEN,ID_ERR);
    Fid4();
}

void Fid4(){
    Test_Symbole(PF_TOKEN,PF_ERR);
    Fid5();
}

void Fid5(){
    if(SYM_COUR.CODE == ACO_TOKEN){
        Sym_Suiv();
        INSTRUCTIONS();
        Test_Symbole(ACF_TOKEN,ACF_ERR);
    }
    else {
        INSTRUCTION();
    }
}

void Fid3(){
    if(SYM_COUR.CODE == IN_TOKEN){
        Sym_Suiv();
        Test_Symbole(ID_TOKEN,ID_ERR);
        Test_Symbole(ACO_TOKEN,ACO_ERR);
        INSTRUCTIONS();
        Test_Symbole(ACF_TOKEN,ACF_ERR);
    }
    else{
        Test_Symbole(EG_TOKEN,EG_ERR);
        _log(407);
        Test_Symbole(NUM_TOKEN,NUM_ERR);
        Test_Symbole(TO_TOKEN,TO_ERR);
        Test_Symbole(NUM_TOKEN,NUM_ERR);
        Test_Symbole(DO_TOKEN,DO_ERR);
        _log(412);
        INSTRUCTIONS();
        Test_Symbole(PV_TOKEN,PV_ERR);
    }
}

void WHILELOOP_STATEMENT(){
    Test_Symbole(WHILE_TOKEN,WHILE_ERR);
    Fwhile();

}

void Fwhile(){
    Test_Symbole(PO_TOKEN,PO_ERR);
    Fwhile2();
}

void Fwhile2(){
    CONDITIONS();
    FCONDITIONS();
}

void FCONDITIONS(){
    Test_Symbole(PF_TOKEN,PF_ERR);
    FCONDITIONS3();
}

void FCONDITIONS3(){
    if(SYM_COUR.CODE == ACO_TOKEN){
        sym_suiv();
        INSTRUCTIONS();
        Test_Symbole(ACF_TOKEN,ACF_ERR);
    }
    else{
        INSTRUCTION();
    }
}

void DOWHILELOOP_STATEMENT(){
    if(SYM_COUR.CODE == DO_TOKEN){
        Sym_Suiv();
        Test_Symbole(ACO_TOKEN,ACO_ERR);
        INSTRUCTIONS();
        Test_Symbole(ACF_TOKEN,ACF_ERR);
        Test_Symbole(WHILE_TOKEN,WHILE_ERR);
        Test_Symbole(PO_TOKEN,PO_ERR);
        CONDITIONS();
        Test_Symbole(PF_TOKEN,PF_ERR);
        Test_Symbole(PV_TOKEN,PV_ERR);
    }
    else{
        Test_Symbole(REPEAT_TOKEN,REPEAT_ERR);
        INSTRUCTIONS();
        Test_Symbole(UNTIL_TOKEN,UNTIL_TOKEN);
        CONDITIONS();
        Test_Symbole(PV_TOKEN,PV_ERR);
    }
}

void CONDITIONS(){
    if(NOT_TOKEN == SYM_COUR.CODE || SYM_COUR.CODE == NOT1_TOKEN) {
        Sym_Suiv();
        Test_Symbole(PO_TOKEN,PO_ERR);
        CONDITION();
        Test_Symbole(PF_TOKEN,PF_ERR);
    }
    else {
        CONDITION();
        FCONDITION();
    }
}

void FCONDITION(){
    if(SYM_COUR.CODE == AND_TOKEN || SYM_COUR.CODE == OR_TOKEN || SYM_COUR.CODE == AND1_TOKEN || SYM_COUR.CODE == OR1_TOKEN){
        Sym_Suiv();
        CONDITIONS();
    }
        
}

void CONDITION(){
    EXPRESSION();
    COMPARATOR();   // TO IMPLEMENT LATER
    EXPRESSION();
}

void COMPARATOR(){
    switch(SYM_COUR.CODE){
        case(SUP_TOKEN):
            break;
        case(INF_TOKEN):
            break;
        case(INFEG_TOKEN):
            break;
        case(EQU_TOKEN):
            break;
        case(TRIPPLEEQU_TOKEN):
            break;
        case(SUPEG_TOKEN):
            break;
        case(DIFF1_TOKEN):
            break;
        default:
            erreur_syntaxique(COMPARATOR_ERR);
    }
    Sym_Suiv();
}

void INPUT_OUTPUT(){
    if(SYM_COUR.CODE == PRINT_TOKEN || SYM_COUR.CODE == PRINTF_TOKEN || SYM_COUR.CODE == SCANF_TOKEN || SYM_COUR.CODE == INPUT_TOKEN ||
        SYM_COUR.CODE == LOG_TOKEN || SYM_COUR.CODE == FPRINTF_TOKEN || SYM_COUR.CODE == FSCANF_TOKEN || SYM_COUR.CODE == WRITE_TOKEN || SYM_COUR.CODE == READ_TOKEN || SYM_COUR.CODE == PUTS_TOKEN || SYM_COUR.CODE == GETS_TOKEN){
            Sym_Suiv();
            _log(521);
            Test_Symbole(PO_TOKEN,PO_ERR);
            ARGUMENT();
            Test_Symbole(PF_TOKEN,PF_TOKEN);
            Test_Symbole(PV_TOKEN,PV_ERR);
    }
}

// void FONCTION(){
//     if(SYM_COUR.CODE == DEF_TOKEN){
//         Test_Symbole(TYPE_TOKEN, TYPE_ERR);
//         FONCTION2();
//     }
//     else{
//         Test_Symbole(FUNCTION_TOKEN, FUNTION_ERR);
//         Test_Symbole(TYPE_TOKEN,TYPE_ERR);
//         FONCTION2();
//     }
// }

void FONCTION(){
    if(SYM_COUR.CODE==DEF_TOKEN||SYM_COUR.CODE==FUNCTION_TOKEN){
        Sym_Suiv();
        TYPE();
        _log(544);
        FONCTION2();
    }
}

void FONCTION2(){
    Test_Symbole(ID_TOKEN, ID_ERR);
    _log(551);
    Test_Symbole(PO_TOKEN, PO_ERR);
    PARAMETER();
    Test_Symbole(PF_TOKEN, PF_ERR);
    _log(555);
    Test_Symbole(ACO_TOKEN, ACO_TOKEN);
    _log(557);
    INSTRUCTIONS();
    Test_Symbole(ACF_TOKEN, ACF_TOKEN);
    _log(558);
}

void PARAMETER(){
    Test_Symbole(ID_TOKEN,ID_ERR);
    Test_Symbole(PTS_TOKEN,PTS_ERR);   // added new 
    TYPE();
    PARAMETER1();
}

void PARAMETER1(){
    if (SYM_COUR.CODE == VIR_TOKEN)
    {
        Sym_Suiv();
        Test_Symbole(ID_TOKEN,ID_ERR);
        Test_Symbole(PTS_TOKEN,PTS_ERR);   // added new 
        TYPE();
        _log(573);
        PARAMETER1();
    }
}

void CONTROLE (){
    switch(SYM_COUR.CODE){
        case IF_TOKEN : IF(); break;
        case CASE_TOKEN: CASE(); break;
        case PO_TOKEN: SHORTHAND(); break;
        default : printf("controle error");
    }
}

void IF(){
    Test_Symbole(IF_TOKEN,IF_ERR); 
    FIF();
}

void FIF(){
    Test_Symbole(PO_TOKEN, PO_ERR);
    FIF2();
}

void FIF2(){
    CONDITION(); 
    FCONDITION1();
}

void FCONDITION1() {
    Test_Symbole(PF_TOKEN, PF_ERR);
    FCONDITION2();
}

void FCONDITION2(){
    BLOCK_IF(); 
    FBLOCK_IF();
}

void FBLOCK_IF(){
    if(SYM_COUR.CODE==ELSE_TOKEN){
        Sym_Suiv();
        BLOCK_IF();
    }
    else if (SYM_COUR.CODE == ELIF_TOKEN){
        Sym_Suiv();
        BLOCK_IF();    
        Test_Symbole(ELSE_TOKEN,ELSE_ERR);
        BLOCK_IF();
    }
}

void BLOCK_IF(){
    Test_Symbole(ACO_TOKEN, ACO_ERR);
    INSTRUCTIONS();
    Test_Symbole(ACF_TOKEN, ACF_ERR);
}

void CASE(){
    Test_Symbole(SWITCH_TOKEN,SWITCH_ERR);
    Test_Symbole(PO_TOKEN, PO_ERR);
    EXPRESSION();
    Test_Symbole(PF_TOKEN, PF_ERR);
    Test_Symbole(ACO_TOKEN, ACO_ERR);
    BLOCK_CASE();
    Test_Symbole(ACF_TOKEN, ACF_ERR);
}

void BLOCK_CASE(){
    if(SYM_COUR.CODE==CASE_TOKEN){
        Sym_Suiv();
        Fcase();
    }else if(SYM_COUR.CODE==DEFAULT_TOKEN){
        Sym_Suiv();
        Test_Symbole(PTS_TOKEN, PTS_ERR);
        INSTRUCTIONS();
    }
}

void Fcase(){
    FACTEUR();
    FFACTEUR1();
}

void FFACTEUR1(){
    Test_Symbole(PTS_TOKEN, PTS_ERR);
    FFACTEUR2();
}

void FFACTEUR2(){
    INSTRUCTIONS(); 
    FINSTRUCTIONS();
}

void FINSTRUCTIONS(){
    if (SYM_COUR.CODE == CASE_TOKEN || SYM_COUR.CODE == DEFAULT_TOKEN)
        BLOCK_CASE();
}

void SHORTHAND(){
    Test_Symbole(PO_TOKEN, PO_ERR);
    CONDITION();
    Test_Symbole(PF_TOKEN, PF_ERR);
    Test_Symbole(INTERROGATION_TOKEN, INTERROGATION_ERR);
    INSTRUCTION();
    Test_Symbole(PTS_TOKEN, PTS_ERR);
    INSTRUCTION();
}

void VAR_DECLARATION(){
    switch (SYM_COUR.CODE){
        case CONST_TOKEN:
            Sym_Suiv();
            TYPE();
            IDS_CONST();
            break;
        case LET_TOKEN: 
            Sym_Suiv();
            VARS2();
            break;
    }
}

void VARS2(){
    Test_Symbole(ID_TOKEN,ID_ERR);
    Fid1();
}

void Fid1(){
    VARS_TYPE();
    FVARS_TYPE();
}

void FVARS_TYPE(){
    if(SYMBOLE_AFF() == 1)
    {
        Sym_Suiv();
        Fsymbole_aff1();
    }
    else if(SYM_COUR.CODE == VIR_TOKEN)
    {
        Sym_Suiv();
        VARS2();
    }
}

int SYMBOLE_AFF(){
    if (SYM_COUR.CODE == EG_TOKEN 
        || SYM_COUR.CODE == AFFECARROW_TOKEN
        || SYM_COUR.CODE == AFFECPASCAL_TOKEN  
        || SYM_COUR.CODE == AFFECT_TOKEN
        )
        return 1;
    else
        return 0;
}

void Fsymbole_aff1(){
    EXPRESSION(); 
    FEXPRESSION1();
}

void FEXPRESSION1(){
    switch (SYM_COUR.CODE){
        case VIR_TOKEN :Sym_Suiv(); VARS2(); break;
        default: break;
    }
}

void VARS_TYPE(){
    if(SYM_COUR.CODE==PTS_TOKEN|SYM_COUR.CODE==IS_TOKEN){
        Sym_Suiv();
        TYPE();
    }
}

void IDS_CONST(){
    Test_Symbole(ID_TOKEN,ID_ERR);
    Fid2();
}

void Fid2(){
    if (SYMBOLE_AFF() == 1) {
        Sym_Suiv();
        Fsymbole_aff();
    }
    
}

void Fsymbole_aff(){
    EXPRESSION();
    FEXPRESSION();
}

void FEXPRESSION(){
    switch (SYM_COUR.CODE){
        case VIR_TOKEN :Sym_Suiv(); IDS_CONST(); break;
        default : break;
    }
}

void TYPE(){
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
            SYM_COUR.CODE== AUTO_TOKEN||SYM_COUR.CODE== VOID_TOKEN)
            Sym_Suiv();
    else
        erreur_syntaxique(TYPE_ERR);
}

void erreur_syntaxique(ERREURS e)
{
    good = false;
    printf("%s\n", ERR[e]);
}
