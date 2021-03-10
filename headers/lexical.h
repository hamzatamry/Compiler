#ifndef LEXICAL_H 
#define LEXICAL_H
#include <stdio.h>
typedef enum 
{
    INT_TOKEN, INTEGER_TOKEN, NUMBER_TOKEN, FLOAT_TOKEN, CHAR_TOKEN, STRING_TOKEN, STR_TOKEN, LONG_TOKEN, DOUBLE_TOKEN, SHORT_TOKEN,
    UNSIGNED_TOKEN, BOOLEAN_TOKEN, BOOL_TOKEN, LET_TOKEN, $_TOKEN, BYTE_TOKEN, AUTO_TOKEN, VOID_TOKEN, TRUE_TOKEN, FALSE_TOKEN, 
    PROGRAM_TOKEN, CONST_TOKEN, VAR_TOKEN, BEGIN_TOKEN, END_TOKEN, IF_TOKEN, THEN_TOKEN, WHILE_TOKEN, DO_TOKEN, READ_TOKEN, WRITE_TOKEN,
    SWITCH_TOKEN, GOTO_TOKEN, DEF_TOKEN, FUNCTION_TOKEN, PV_TOKEN, PT_TOKEN, PTS_TOKEN, PLUS_TOKEN, ADD_TOKEN, MOINS_TOKEN, MINUS_TOKEN, MULT_TOKEN,
    MULT1_TOKEN, DIV_TOKEN, DIV1_TOKEN, PER_TOKEN, MOD_TOKEN, MOD1_TOKEN, MODULO_TOKEN, VIR_TOKEN, EG_TOKEN, AFFECPASCAL_TOKEN, AFFECT_TOKEN,
    AFFECARROW_TOKEN, INF_TOKEN, LSS_TOKEN, INFEG_TOKEN, LEQ_TOKEN, SUP_TOKEN, GTR_TOKEN, SUPEG_TOKEN, GEQ_TOKEN, EQU_TOKEN, EQU1_TOKEN, IS_TOKEN, 
    TRIPPLEEQU_TOKEN, IN_TOKEN, PUISS_TOKEN, PUISSAFFEC_TOKEN, ADDAFFEC_TOKEN, MINUSAFFEC_TOKEN, MULTAFFEC_TOKEN, DIVAFFEC_TOKEN, MODAFFEC_TOKEN,
    BXORAFFEC_TOKEN, BANDAFFEC_TOKEN, BORAFFEC_TOKEN, INCREM_TOKEN, DECREM_TOKEN, DIFF_TOKEN, PO_TOKEN, PF_TOKEN, DC_TOKEN, FC_TOKEN, ACO_TOKEN, ACF_TOKEN,
    BXOR_TOKEN, TILD_TOKEN, LEFTSHIFT_TOKEN, RIGHTSHIFT_TOKEN, BAND_TOKEN, BOR_TOKEN, AND_TOKEN, AND1_TOKEN, OR_TOKEN, OR1_TOKEN, NOT_TOKEN, NOT1_TOKEN,
    QUOTE_TOKEN,SINGLEQUOTE_TOKEN, EOF_TOKEN, ID_TOKEN, NUM_TOKEN, ELSE_TOKEN, UNTIL_TOKEN, REPEAT_TOKEN, FOR_TOKEN, DOWNTO_TOKEN, CASE_TOKEN, OF_TOKEN,
    INTO_TOKEN , RETURN_TOKEN, PRINT_TOKEN, PRINTF_TOKEN, SCANF_TOKEN, INPUT_TOKEN, LOG_TOKEN, FPRINTF_TOKEN, FSCANF_TOKEN, FREAD_TOKEN, FWRITE_TOKEN, 
    PUTS_TOKEN, GETS_TOKEN, CALL_TOKEN, STRINGVAL_TOKEN, ERREUR_TOKEN, CHAR_VALUE_TOKEN, INTERROGATION_TOKEN, TO_TOKEN, ELIF_TOKEN
} CODES_LEX;


typedef struct
{
    CODES_LEX CODE;
    char NOM[20];
} TSym_Cour;

// typedef enum 
// {
//     NUM_ERR, CHAR_ERR, FICH_VID_ERR, ID_LONG_ERR, ID_INC_ERR, COMMENT_ERR, STRING_ERR
// } ERREURS;

typedef enum 
{
    NUM_ERR, CHAR_ERR, FICH_VID_ERR, ID_LONG_ERR, ID_INC_ERR, COMMENT_ERR, STRING_ERR,
    PROGRAM_ERR, CONST_ERR, VAR_ERR, BEGIN_ERR, END_ERR, IF_ERR, THEN_ERR, WHILE_ERR,
    DO_ERR, READ_ERR, WRITE_ERR, PV_ERR, PT_ERR, PTS_ERR, PLUS_ERR, MOINS_ERR, MULT_ERR, DIV_ERR,
    VIR_ERR, EG_ERR, AFF_ERR, INF_ERR, INFEG_ERR, SUP_ERR, SUPEG_ERR, DIFF_ERR, PO_ERR, PF_ERR,
    DC_ERR, FC_ERR, ACO_ERR, ACF_ERR, EOF_ERR, ID_ERR, ELSE_ERR, UNTIL_ERR, REPEAT_ERR, FOR_ERR,
    DOWNTO_ERR, CASE_ERR, OF_ERR, INTO_ERR ,CONST_VAR_BEGIN_ERR, INST_ERR, FACT_ERR, POUR_ERR, ERR_FICH_VID,
    CAS_ERR, DOUBLONS_ERR, CONST_MODIF_ERR, UNDECLARED_ERR, PRO_ID_ERR, TYPE_ERR, VARS_TYPE_ERR,INCREM_ERR, DECREM_ERR,CALL_ERR,
    RETURN_ERR,EQU_ERR,TO_ERR,INTERROGATION_ERR,ELIF_ERR,COMPARATOR_ERR
} ERREURS;

// Error MESSAGE_ERR[100] = {
//     { NUM_ERR     , "Valeur numero incorrecte" },
//     { CHAR_ERR, "Valeur caractere incorrecte" },
//     { FICH_VID_ERR, "fichier vide" },
//     { ID_LONG_ERR, "identificateur long" },
//     { ID_INC_ERR, "identificateur incorrect" },
//     { COMMENT_ERR, "erreur commentaire" },
//     { STRING_ERR, "string non proprement declare : missing \"" }
// };

char ERR[][100] = {
    "Valeur numero incorrecte", "Valeur caractere incorrecte", "fichier vide", "fichier vide", "identificateur long", "identificateur incorrect" ,"erreur commentaire",
    "string non proprement declare : missing \"", "erreur program","erreur constante", "erreur variable","erreur begin","End Erreur", "if erreur", "then erreur","While erreur",
    "Do erreur","Erreur READ","WRITE erreur","Point virgule erreur","point erreur","double points erreur","plus erreur","monis erreur","multiplication erreur",
    "division erreur", "virgule erreur", "egale erreur", "affectation erreur", "inferieur erreur", "inferieur ou egale erreur", "superieur erreur", "superieur ou egale erreur",
    "different erreur","parenthese ouvrante erreur", "parenthese fermante erreur", "debut commentaire erreur", "fin commentaire erreur", "accolade ouvrante erreur",
    "accolade fermante erreur", "fin de fichier erreur", "identificateur erreur","else erreur", "until erreur", "repeat erreur", "for erreur",
    "downto erreur", "case erreur", "of erreur", "into erreur", "erreur debut programme", "instruction erreur", "facteur erreur", "pour erreur", "fichier vide",
    "cas erreur","erreur doublons","erreur modification constante", "erreur identificateur non declare", "erreur identificateur du programme non autorise", "erreur declaration type" ,
    "erreur is or :","erreur dans incrementation","erreur dans decrementation","call erreur","return erreur","EQU_ERR","TO_ERR","INTERROGATION_ERR","ELIF_ERR", "NUM_ERR","COMPARATOR_ERR"
};


typedef struct
{
    ERREURS CODE;
    char msg[50];  
} Error;

extern void ouvrir_fichier(char nom[20]);
extern _Bool isSpecial();
extern void lire_car();
extern _Bool isSeparator();
extern void isID();
extern void isString();
extern void isChar();
extern int  mot_cle();
extern void lire_mots();
extern void lire_nombres();
extern void lire_speacials();
extern void sym_suiv();
extern void afficher_token();
extern void ERREUR(ERREURS e);

extern char Car_Cour;
extern TSym_Cour SYM_COUR;
extern FILE* flux_output;
extern FILE* flux_input;

#endif




