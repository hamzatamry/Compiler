#ifndef SEMANTIQUE_SYNTAXIQUE_H
#define SEMANTIQUE_SYNTAXIQUE_H
#include <stdio.h>
#include <stdbool.h>


extern FILE *f;
extern bool good;  // variale globale indiquant si l'analyseur syntaxique valide ou pas le fichier

typedef enum {
    INT_TOKEN, INTEGER_TOKEN, NUMBER_TOKEN, FLOAT_TOKEN, CHAR_TOKEN, STRING_TOKEN, STR_TOKEN, LONG_TOKEN,
    DOUBLE_TOKEN, SHORT_TOKEN, UNSIGNED_TOKEN, BOOLEAN_TOKEN, BOOL_TOKEN, LET_TOKEN, $_TOKEN, BYTE_TOKEN, AUTO_TOKEN,
    PROGRAM_TOKEN, CONST_TOKEN, VAR_TOKEN, BEGIN_TOKEN, END_TOKEN, IF_TOKEN, THEN_TOKEN, WHILE_TOKEN, DO_TOKEN, READ_TOKEN, WRITE_TOKEN,
    SWITCH_TOKEN, GOTO_TOKEN, DEF_TOKEN, FUNCTION_TOKEN, PV_TOKEN, PT_TOKEN, PTS_TOKEN, PLUS_TOKEN, ADD_TOKEN, MOINS_TOKEN, MINUS_TOKEN, MULT_TOKEN,
    MULT1_TOKEN, DIV_TOKEN, DIV1_TOKEN, PER_TOKEN, MOD_TOKEN, MOD1_TOKEN, MODULO_TOKEN, VIR_TOKEN, EG_TOKEN, AFFECPASCAL_TOKEN, AFFECT_TOKEN,
    AFFECARROW_TOKEN, INF_TOKEN, LSS_TOKEN, INFEG_TOKEN, LEQ_TOKEN, SUP_TOKEN, GTR_TOKEN, SUPEG_TOKEN, GEQ_TOKEN, EQU_TOKEN, EQU1_TOKEN, IS_TOKEN,
    TRIPPLEEQU_TOKEN, IN_TOKEN, PUISS_TOKEN, PUISSAFFEC_TOKEN, ADDAFFEC_TOKEN, MINUSAFFEC_TOKEN, MULTAFFEC_TOKEN, DIVAFFEC_TOKEN, MODAFFEC_TOKEN,
    BXORAFFEC_TOKEN, BANDAFFEC_TOKEN, BORAFFEC_TOKEN, INCREM_TOKEN, DECREM_TOKEN, DIFF_TOKEN, PO_TOKEN, PF_TOKEN, DC_TOKEN, FC_TOKEN, ACO_TOKEN, ACF_TOKEN,
    BXOR_TOKEN, TILD_TOKEN, LEFTSHIFT_TOKEN, RIGHTSHIFT_TOKEN, BAND_TOKEN, BOR_TOKEN, AND_TOKEN, AND1_TOKEN, OR_TOKEN, OR1_TOKEN, NOT_TOKEN, NOT1_TOKEN,
    EOF_TOKEN, ID_TOKEN, NUM_TOKEN, ELSE_TOKEN, UNTIL_TOKEN, REPEAT_TOKEN, FOR_TOKEN, DOWNTO_TOKEN, CASE_TOKEN, OF_TOKEN, INTO_TOKEN , ERREUR_TOKEN
}CODES_LEX;

typedef struct {
    CODES_LEX CODE;
    char NOM[20];
}TSym_Cour;


TSym_Cour SYM_COUR;

typedef enum {
    PROGRAM_ERR, CONST_ERR, VAR_ERR, BEGIN_ERR, END_ERR, IF_ERR, THEN_ERR, WHILE_ERR,
    DO_ERR, READ_ERR, WRITE_ERR, PV_ERR, PT_ERR, PTS_ERR, PLUS_ERR, MOINS_ERR, MULT_ERR, DIV_ERR,
    VIR_ERR, EG_ERR, AFF_ERR, INF_ERR, INFEG_ERR, SUP_ERR, SUPEG_ERR, DIFF_ERR, PO_ERR, PF_ERR,
    DC_ERR, FC_ERR, ACO_ERR, ACF_ERR, EOF_ERR, ID_ERR, NUM_ERR, ELSE_ERR, UNTIL_ERR, REPEAT_ERR, FOR_ERR,
    DOWNTO_ERR, CASE_ERR, OF_ERR, INTO_ERR ,CONST_VAR_BEGIN_ERR, INST_ERR, FACT_ERR, POUR_ERR, ERR_FICH_VID,
    CAS_ERR, DOUBLONS_ERR, CONST_MODIF_ERR, UNDECLARED_ERR, PRO_ID_ERR, TYPE_ERR, VARS_TYPE_ERR
}ERREURS;

typedef enum {
    TPROG, TCONST, TVAR
    }TSYM;

typedef struct {
    char NOM[20];
    TSYM TIDF;
} T_TAB_IDF;

T_TAB_IDF TAB_IDFS[50];


char previous[20];


extern void ouvrir_fichier(char nom[20]);
extern void Test_Symbole(CODES_LEX lex,ERREURS err);
extern void Sym_Suiv();
/* extern void PROGRAM();
extern void BLOCK();
extern void CONSTS();
extern void VARS();
extern void INSTS();
extern void INST();
extern void AFFEC();
extern void SI();
extern void TANTQUE();
extern void ECRIRE();
extern void LIRE();
extern void COND();
extern void EXPR();
extern void TERM();
extern void FACT();
extern void SI();
extern void REPETER();
extern void POUR();
extern void CAS();
extern void CONTROL();
extern void IF();
extern void CASE();
extern void BLOCK_CASE(); */

extern void PROGRAM();
extern void INSTRUCTIONS();
extern void INSTRUCTION();
extern void INST1();
extern void ACC_O();
extern void ACC_F();
extern void AFFECTATION();
extern void APPEL_FONCTION();
extern void BOUCLE();
extern void RETURN();
extern void VAR_DECLARATION();
extern void FONCTION();
extern void CONTROLE();
extern void EXCEPTION();
extern void FILEHANDLING();
extern void AFFECTATION1();
extern void SYMBOLE_AFF();
extern void ID();
extern void EXPRESSION();
extern void EG();
extern void TERM();
extern void EX1();
extern void OPPERATEURADD();
extern void VARS1();
extern void TYPE();
extern void IDS_CONST();
extern void JS_IDS();
extern void VARS2();
extern void VARS_TYPE();
extern void OPT();
extern void VARS3();
extern void IDS();
extern void IDS1();
extern void JS1();
extern void IDS2();
extern void IF_STMT();
extern void COND();
extern void IF_STMT_SYMB();
extern void SUITE1();
extern void END();
extern void SWITCH();
extern void SWITCH_IF();
extern void STATEMENT();
extern void SUITE_IF();
extern void ELIF_STMT();
extern void ELSE_BLOCK();
extern void ELIF_SUITE();
extern void SHORTHAND();
extern void DOWHILELOOP_STATEMENT();
extern void STATEMENTS();
extern void CONDITION();
extern void FORLOOP_STATEMENT();
extern void A_F();
extern void B_F();
extern void AF1();
extern void NOMBRE();
extern void B_F1();
extern void WHILELOOP_STATEMENT();
extern void A_W();
extern void B_W();
extern void PARAMETERS();
extern void FONCTION1();
extern void PARAMETER();
extern void OPPERATEURSPECIAUX();
extern void COMPAR();
extern void OPPERATEURMULT();
extern void STRING();








extern void ERREUR(ERREURS e);

extern void addID(TSYM type);
extern void semCheck(int accepted);



#endif
