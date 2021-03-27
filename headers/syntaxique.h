#ifndef SYNTAXIQUE_H
#define SYNTAXIQUE_H
#include "..\..\analyseur_lexical\headers\lexical.h"

// typedef enum 
// {
//     INT_TOKEN, INTEGER_TOKEN, NUMBER_TOKEN, FLOAT_TOKEN, CHAR_TOKEN, STRING_TOKEN, STR_TOKEN, LONG_TOKEN, DOUBLE_TOKEN, SHORT_TOKEN,
//     UNSIGNED_TOKEN, BOOLEAN_TOKEN, BOOL_TOKEN, LET_TOKEN, $_TOKEN, BYTE_TOKEN, AUTO_TOKEN, VOID_TOKEN, TRUE_TOKEN, FALSE_TOKEN, 
//     PROGRAM_TOKEN, CONST_TOKEN, VAR_TOKEN, BEGIN_TOKEN, END_TOKEN, IF_TOKEN, THEN_TOKEN, WHILE_TOKEN, DO_TOKEN, READ_TOKEN, WRITE_TOKEN,
//     SWITCH_TOKEN, GOTO_TOKEN, DEF_TOKEN, FUNCTION_TOKEN, PV_TOKEN, PT_TOKEN, PTS_TOKEN, PLUS_TOKEN, ADD_TOKEN, MOINS_TOKEN, MINUS_TOKEN, MULT_TOKEN,
//     MULT1_TOKEN, DIV_TOKEN, DIV1_TOKEN, PER_TOKEN, MOD_TOKEN, MOD1_TOKEN, MODULO_TOKEN, VIR_TOKEN, EG_TOKEN, AFFECPASCAL_TOKEN, AFFECT_TOKEN,
//     AFFECARROW_TOKEN, INF_TOKEN, LSS_TOKEN, INFEG_TOKEN, LEQ_TOKEN, SUP_TOKEN, GTR_TOKEN, SUPEG_TOKEN, GEQ_TOKEN, EQU_TOKEN, EQU1_TOKEN, IS_TOKEN, 
//     TRIPPLEEQU_TOKEN, IN_TOKEN, PUISS_TOKEN, PUISSAFFEC_TOKEN, ADDAFFEC_TOKEN, MINUSAFFEC_TOKEN, MULTAFFEC_TOKEN, DIVAFFEC_TOKEN, MODAFFEC_TOKEN,
//     BXORAFFEC_TOKEN, BANDAFFEC_TOKEN, BORAFFEC_TOKEN, INCREM_TOKEN, DECREM_TOKEN, DIFF_TOKEN, PO_TOKEN, PF_TOKEN, DC_TOKEN, FC_TOKEN, ACO_TOKEN, ACF_TOKEN,
//     BXOR_TOKEN, TILD_TOKEN, LEFTSHIFT_TOKEN, RIGHTSHIFT_TOKEN, BAND_TOKEN, BOR_TOKEN, AND_TOKEN, AND1_TOKEN, OR_TOKEN, OR1_TOKEN, NOT_TOKEN, NOT1_TOKEN,
//     QUOTE_TOKEN,SINGLEQUOTE_TOKEN, EOF_TOKEN, ID_TOKEN, NUM_TOKEN, ELSE_TOKEN, UNTIL_TOKEN, REPEAT_TOKEN, FOR_TOKEN, DOWNTO_TOKEN, CASE_TOKEN, OF_TOKEN,
//     INTO_TOKEN , RETURN_TOKEN, PRINT_TOKEN, PRINTF_TOKEN, SCANF_TOKEN, INPUT_TOKEN, LOG_TOKEN, FPRINTF_TOKEN, FSCANF_TOKEN, FREAD_TOKEN, FWRITE_TOKEN, 
//     PUTS_TOKEN, GETS_TOKEN, CALL_TOKEN, STRINGVAL_TOKEN, ERREUR_TOKEN
// } CODES_LEX;

// typedef struct 
// {
//     CODES_LEX CODE;
//     char NOM[20];
// }   TSym_Cour;


// TSym_Cour SYM_COUR;

// typedef enum 
// {
//     PROGRAM_ERR, CONST_ERR, VAR_ERR, BEGIN_ERR, END_ERR, IF_ERR, THEN_ERR, WHILE_ERR,
//     DO_ERR, READ_ERR, WRITE_ERR, PV_ERR, PT_ERR, PTS_ERR, PLUS_ERR, MOINS_ERR, MULT_ERR, DIV_ERR,
//     VIR_ERR, EG_ERR, AFF_ERR, INF_ERR, INFEG_ERR, SUP_ERR, SUPEG_ERR, DIFF_ERR, PO_ERR, PF_ERR,
//     DC_ERR, FC_ERR, ACO_ERR, ACF_ERR, EOF_ERR, ID_ERR, ELSE_ERR, UNTIL_ERR, REPEAT_ERR, FOR_ERR,
//     DOWNTO_ERR, CASE_ERR, OF_ERR, INTO_ERR ,CONST_VAR_BEGIN_ERR, INST_ERR, FACT_ERR, POUR_ERR, ERR_FICH_VID,
//     CAS_ERR, DOUBLONS_ERR, CONST_MODIF_ERR, UNDECLARED_ERR, PRO_ID_ERR, TYPE_ERR, VARS_TYPE_ERR,INCREM_ERR, DECREM_ERR
// }   ERREURS;

extern FILE* lexical_output;
extern _Bool good;  // variale globale indiquant si l'analyseur syntaxique valide ou pas le fichier
extern void ouvrir_fichier_syntaxique(char nom[20]);
extern void Test_Symbole(CODES_LEX lex, ERREURS err);
extern void Sym_Suiv();
extern void PROGRAM();
extern void INSTRUCTIONS();
extern void FINSTRUCTION();
extern void INSTRUCTION();
extern void AFFECTATION();
extern void Fid();
extern void EXPRESSION();
extern void FTERM();
extern void TERM();
extern void FFACTEUR();
extern void FACTEUR();
extern void APPEL_FONCTION();
extern void APPEL_FONCTION_ARG();
extern void ARGUMENT();
extern void ARGUMENT1();
extern void RETURN();
extern void BOUCLE();
extern void FORLOOP_STATEMENT();
extern void Ffor();
extern int isMultp(int TOKEN);
extern int isTermBeg2(int TOKEN);
extern int isTermBeg(int TOKEN);
extern int isIO(int TOKEN);
extern void FOR1();
extern void FVAR_DECLARATION();
extern void FVAR_DECLARATION2();
extern void FCONDITIONS1();
extern void FCONDITIONS2();
extern void FINSTRUCTION1();
extern void FINSTRUCTION2();
extern void FVAR_DECLARATION3();
extern void COMPARATOR();
extern void Fid4();
extern void Fid5();
extern void Fid3();
extern void WHILELOOP_STATEMENT();
extern void Fwhile();
extern void Fwhile2();
extern void FCONDITIONS();
extern void FCONDITIONS3();
extern void DOWHILELOOP_STATEMENT();
extern void CONDITIONS();
extern void FCONDITION();
extern void CONDITION();
extern void INPUT_OUTPUT();
extern void FONCTION();
extern void FONCTION2();
extern void PARAMETER();
extern void PARAMETER1();
extern void CONTROLE ();
extern void IF();
extern void FIF();
extern void FIF2();
extern void FCONDITION1();
extern void FCONDITION2();
extern void FBLOCK_IF();
extern void BLOCK_IF();
extern void CASE();
extern void BLOCK_CASE();
extern void Fcase();
extern void FFACTEUR1();
extern void FFACTEUR2();
extern void FINSTRUCTIONS();
extern void SHORTHAND();
extern void VAR_DECLARATION();
extern void VARS2();
extern void Fid1();
extern void FVARS_TYPE();
extern void Fsymbole_aff1();
extern void FEXPRESSION();
extern void VARS_TYPE();
extern void IDS_CONST();
extern void Fid2();
extern int SYMBOLE_AFF();
extern void Fsymbole_aff();
extern void FEXPRESSION1();
extern void TYPE();
extern int isType();


extern void erreur_syntaxique(ERREURS e);

#endif
