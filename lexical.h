#ifndef LEXICAL_H 
#define LEXICAL_H
#include <stdio.h>
#include <stdbool.h>

typedef enum {
    INT_TOKEN, INTEGER_TOKEN, NUMBER_TOKEN, FLOAT_TOKEN, CHAR_TOKEN, STRING_TOKEN, STR_TOKEN, LONG_TOKEN,
    DOUBLE_TOKEN, SHORT_TOKEN, UNSIGNED_TOKEN, BOOLEAN_TOKEN, BOOL_TOKEN, LET_TOKEN, $_TOKEN, BYTE_TOKEN, AUTO_TOKEN, VOID_TOKEN, TRUE_TOKEN, FALSE_TOKEN, 
    PROGRAM_TOKEN, CONST_TOKEN, VAR_TOKEN, BEGIN_TOKEN, END_TOKEN, IF_TOKEN, THEN_TOKEN, WHILE_TOKEN, DO_TOKEN, READ_TOKEN, WRITE_TOKEN,
    SWITCH_TOKEN, GOTO_TOKEN, DEF_TOKEN, FUNCTION_TOKEN, PV_TOKEN, PT_TOKEN, PTS_TOKEN, PLUS_TOKEN, ADD_TOKEN, MOINS_TOKEN, MINUS_TOKEN, MULT_TOKEN,
    MULT1_TOKEN, DIV_TOKEN, DIV1_TOKEN, PER_TOKEN, MOD_TOKEN, MOD1_TOKEN, MODULO_TOKEN, VIR_TOKEN, EG_TOKEN, AFFECPASCAL_TOKEN, AFFECT_TOKEN,
    AFFECARROW_TOKEN, INF_TOKEN, LSS_TOKEN, INFEG_TOKEN, LEQ_TOKEN, SUP_TOKEN, GTR_TOKEN, SUPEG_TOKEN, GEQ_TOKEN, EQU_TOKEN, EQU1_TOKEN, IS_TOKEN, 
    TRIPPLEEQU_TOKEN, IN_TOKEN, PUISS_TOKEN, PUISSAFFEC_TOKEN, ADDAFFEC_TOKEN, MINUSAFFEC_TOKEN, MULTAFFEC_TOKEN, DIVAFFEC_TOKEN, MODAFFEC_TOKEN,
    BXORAFFEC_TOKEN, BANDAFFEC_TOKEN, BORAFFEC_TOKEN, INCREM_TOKEN, DECREM_TOKEN, DIFF_TOKEN, PO_TOKEN, PF_TOKEN, DC_TOKEN, FC_TOKEN, ACO_TOKEN, ACF_TOKEN,
    BXOR_TOKEN, TILD_TOKEN, LEFTSHIFT_TOKEN, RIGHTSHIFT_TOKEN, BAND_TOKEN, BOR_TOKEN, AND_TOKEN, AND1_TOKEN, OR_TOKEN, OR1_TOKEN, NOT_TOKEN, NOT1_TOKEN,
    EOF_TOKEN, ID_TOKEN, NUM_TOKEN, ELSE_TOKEN, UNTIL_TOKEN, REPEAT_TOKEN, FOR_TOKEN, DOWNTO_TOKEN, CASE_TOKEN, OF_TOKEN, INTO_TOKEN , RETURN_TOKEN, ERREUR_TOKEN
}CODES_LEX;

typedef enum {
  FICH_VID_ERR, ID_LONG_ERR, ID_INC_ERR, COMMENT_ERR, NUM_LONG_ERR
}ERREURS;

typedef struct
{
    ERREURS CODE;
    char msg[50];  
}Error;



extern void ouvrir_fichier(char nom[20]);
extern bool isSpecial();
extern void lire_car();
extern bool isSeparator();
extern void isID();
extern int  mot_cle();
extern void lire_mots();
extern void lire_nombres();
extern void lire_speacials();
extern void sym_suiv();
extern void afficher_token();
extern void ERREUR(ERREURS e);

extern char Car_Cour;
extern FILE *g;
extern FILE *f;

#endif




