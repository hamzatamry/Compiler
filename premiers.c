#include "symboles.h"
#include "premiers.h"
//#include <stdio.h>

void initialise_premiers(void){
  int i,j;

  // Initialiser toutes les cases du tableau à 0
  for(i=0; i <= NB_NON_TERMINAUX; i++)
    for(j=0; j <= NB_TERMINAUX; j++)
      premiers[i][j] = 0;

  /************************************
    PG
  ************************************/
  premiers[_programme_][ENTIER] = 1;
  premiers[_programme_][ID_FCT] = 1;
  premiers[_programme_][EPSILON] = 1;

  /************************************
    ODV
  ************************************/
  premiers[_optDecVariables_][ENTIER] = 1;
  premiers[_optDecVariables_][EPSILON] = 1;

  /************************************
    LDV
  ************************************/
  premiers[_listeDecVariables_][ENTIER] = 1;

  /************************************
    LDVB
  ************************************/
  premiers[_listeDecVariablesBis_][VIRGULE] = 1;
  premiers[_listeDecVariablesBis_][EPSILON] = 1;

  /************************************
    DV
  ************************************/
  premiers[_declarationVariable_][ENTIER] = 1;

  /************************************
    OTT
  ************************************/
  premiers[_optTailleTableau_][CROCHET_OUVRANT] = 1;
  premiers[_optTailleTableau_][EPSILON] = 1;

  /************************************
    LDF
  ************************************/
  premiers[_listeDecFonctions_][ID_FCT] = 1;
  premiers[_listeDecFonctions_][EPSILON] = 1;

  /************************************
    DF
  ************************************/
  premiers[_declarationFonction_][ID_FCT] = 1;

  /************************************
    LP
  ************************************/
  premiers[_listeParam_][PARENTHESE_OUVRANTE] = 1;

  /************************************
    OLDV
  ************************************/
  premiers[_optListeDecVariables_][ENTIER] = 1;
  premiers[_optListeDecVariables_][EPSILON] = 1;

  /************************************
    I
  ************************************/
  premiers[_instruction_][ID_VAR] = 1;
  premiers[_instruction_][ACCOLADE_OUVRANTE] = 1;
  premiers[_instruction_][SI] = 1;
  premiers[_instruction_][TANTQUE] = 1;
  premiers[_instruction_][ID_FCT] = 1;
  premiers[_instruction_][RETOUR] = 1;
  premiers[_instruction_][ECRIRE] = 1;
  premiers[_instruction_][POINT_VIRGULE] = 1;
  premiers[_instruction_][POUR] = 1;

  /************************************
    IAFF
  ************************************/
  premiers[_instructionAffect_][ID_VAR] = 1;

  /************************************
    IB
  ************************************/
  premiers[_instructionBloc_][ACCOLADE_OUVRANTE] = 1;

  /************************************
    LI
  ************************************/
  premiers[_listeInstructions_][ID_VAR] = 1;
  premiers[_listeInstructions_][ACCOLADE_OUVRANTE] = 1;
  premiers[_listeInstructions_][SI] = 1;
  premiers[_listeInstructions_][TANTQUE] = 1;
  premiers[_listeInstructions_][ID_FCT] = 1;
  premiers[_listeInstructions_][RETOUR] = 1;
  premiers[_listeInstructions_][ECRIRE] = 1;
  premiers[_listeInstructions_][POINT_VIRGULE] = 1;
  premiers[_listeInstructions_][EPSILON] = 1;

  /************************************
    ISI
  ************************************/
  premiers[_instructionSi_][SI] = 1;

  /************************************
    OSINON
  ************************************/
  premiers[_optSinon_][SINON] = 1;
  premiers[_optSinon_][EPSILON] = 1;

  /************************************
    ITQ
  ************************************/
  premiers[_instructionTantque_][TANTQUE]=1;

  /************************************
   IPOUR
  ************************************/
  premiers[_instructionPour_][POUR]=1;

  /************************************
    IAPP
  ************************************/
  premiers[_instructionAppel_][ID_FCT]=1;

  /************************************
    IRET
  ************************************/
  premiers[_instructionRetour_][RETOUR]=1;

  /************************************
    IECR
  ************************************/
  premiers[_instructionEcriture_][ECRIRE]=1;

  /************************************
    IVIDE
  ************************************/
  premiers[_instructionVide_][POINT_VIRGULE]=1;

  /************************************
    EXP
  ************************************/
  premiers[_expression_][NON]=1;
  premiers[_expression_][PARENTHESE_OUVRANTE]=1;
  premiers[_expression_][NOMBRE]=1;
  premiers[_expression_][ID_FCT]=1;
  premiers[_expression_][ID_VAR]=1;
  premiers[_expression_][LIRE]=1;

  /************************************
    EXPB
  ************************************/
  premiers[_expressionBis_][INTERROGATION]=1;
  premiers[_expressionBis_][EPSILON] = 1;

  /************************************
    COND
  ************************************/
  premiers[_condition_][NON]=1;
  premiers[_condition_][PARENTHESE_OUVRANTE]=1;
  premiers[_condition_][NOMBRE]=1;
  premiers[_condition_][ID_FCT]=1;
  premiers[_condition_][ID_VAR]=1;
  premiers[_condition_][LIRE]=1;

  /************************************
    CONDB
  ************************************/
  premiers[_conditionBis_][OU]=1;
  premiers[_conditionBis_][EPSILON] = 1;

  /************************************
    CONJ
  ************************************/
  premiers[_conjonction_][NON]=1;
  premiers[_conjonction_][PARENTHESE_OUVRANTE]=1;
  premiers[_conjonction_][NOMBRE]=1;
  premiers[_conjonction_][ID_FCT]=1;
  premiers[_conjonction_][ID_VAR]=1;
  premiers[_conjonction_][LIRE]=1;

  /************************************
    CONJB
  ************************************/
  premiers[_conjonctionBis_][ET]=1;
  premiers[_conjonctionBis_][EPSILON] = 1;

  /************************************
    NEG
  ************************************/
  premiers[_negation_][NON]=1;
  premiers[_negation_][PARENTHESE_OUVRANTE]=1;
  premiers[_negation_][NOMBRE]=1;
  premiers[_negation_][ID_FCT]=1;
  premiers[_negation_][ID_VAR]=1;
  premiers[_negation_][LIRE]=1;

  /************************************
    COMP
  ************************************/
  premiers[_comparaison_][PARENTHESE_OUVRANTE]=1;
  premiers[_comparaison_][NOMBRE]=1;
  premiers[_comparaison_][ID_FCT]=1;
  premiers[_comparaison_][ID_VAR]=1;
  premiers[_comparaison_][LIRE]=1;

  /************************************
    COMPB
  ************************************/
  premiers[_comparaisonBis_][INFERIEUR]=1;
  premiers[_comparaisonBis_][EGAL]=1;
  premiers[_comparaisonBis_][EPSILON] = 1;


  /************************************
    E
  ************************************/
  premiers[_expArith_][PARENTHESE_OUVRANTE]=1;
  premiers[_expArith_][NOMBRE]=1;
  premiers[_expArith_][ID_FCT]=1;
  premiers[_expArith_][ID_VAR]=1;
  premiers[_expArith_][LIRE]=1;

  /************************************
    EB
  ************************************/
  premiers[_expArithBis_][PLUS]=1;
  premiers[_expArithBis_][MOINS]=1;
  premiers[_expArithBis_][EPSILON] = 1;

  /************************************
    T
  ************************************/
  premiers[_terme_][PARENTHESE_OUVRANTE]=1;
  premiers[_terme_][NOMBRE]=1;
  premiers[_terme_][ID_FCT]=1;
  premiers[_terme_][ID_VAR]=1;
  premiers[_terme_][LIRE]=1;

  /************************************
    TB
  ************************************/
  premiers[_termeBis_][FOIS]=1;
  premiers[_termeBis_][DIVISE]=1;
  premiers[_termeBis_][EPSILON] = 1;

  /************************************
    F
  ************************************/
  premiers[_facteur_][PARENTHESE_OUVRANTE]=1;
  premiers[_facteur_][NOMBRE]=1;
  premiers[_facteur_][ID_FCT]=1;
  premiers[_facteur_][ID_VAR]=1;
  premiers[_facteur_][LIRE]=1;

  /************************************
    VAR
  ************************************/
  premiers[_var_][ID_VAR]=1;

  /************************************
    OIND
  ************************************/
  premiers[_optIndice_][CROCHET_OUVRANT]=1;
  premiers[_optIndice_][EPSILON] = 1;

  /************************************
    APPF
  ************************************/
  premiers[_appelFct_][ID_FCT]=1;

  /************************************
    LEXP
  ************************************/
  premiers[_listeExpressions_][NON]=1;
  premiers[_listeExpressions_][PARENTHESE_OUVRANTE]=1;
  premiers[_listeExpressions_][NOMBRE]=1;
  premiers[_listeExpressions_][ID_FCT]=1;
  premiers[_listeExpressions_][ID_VAR]=1;
  premiers[_listeExpressions_][LIRE]=1;
  premiers[_listeExpressions_][EPSILON] = 1;

  /************************************
    LEXPB
  ************************************/
  premiers[_listeExpressionsBis_][VIRGULE]=1;
  premiers[_listeExpressionsBis_][EPSILON] = 1;

}

int est_premier(int terminal, int non_terminal)
{
  return premiers[non_terminal][terminal];
}
