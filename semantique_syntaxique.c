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

void PROGRAM()
{
    Test_Symbole(PROGRAM_TOKEN, PROGRAM_ERR);
    Test_Symbole(ID_TOKEN, ID_ERR);
    addID(TPROG);
    Test_Symbole(PV_TOKEN, PV_ERR);
    BLOCK();
    Test_Symbole(PT_TOKEN, PT_ERR);
}

void BLOCK()
{
    CONSTS();
    VARS();
    INSTS();
}


void CONSTS() {
    switch (SYM_COUR.CODE)
    {
        case CONST_TOKEN : Sym_Suiv();
                            Test_Symbole(ID_TOKEN, ID_ERR);
                            addID(TCONST);
                            Test_Symbole(EG_TOKEN, EG_ERR);
                            Test_Symbole(NUM_TOKEN, NUM_ERR);
                            Test_Symbole(PV_TOKEN, PV_ERR);
                            while (SYM_COUR.CODE == ID_TOKEN)
                            {
                                addID(TCONST);
                                Sym_Suiv();
                                Test_Symbole(EG_TOKEN, EG_ERR);
                                Test_Symbole(NUM_TOKEN, NUM_ERR);
                                Test_Symbole(PV_TOKEN, PV_ERR);
                            };
                            break;
        case VAR_TOKEN :    break;
        case BEGIN_TOKEN :  break;
        default :           ERREUR(CONST_VAR_BEGIN_ERR);
                            break;
    }
}

void VARS()
{
    switch (SYM_COUR.CODE)
    {
        case VAR_TOKEN :    Sym_Suiv();
                            Test_Symbole(ID_TOKEN, ID_ERR);
                            addID(TVAR);
                            while (SYM_COUR.CODE == VIR_TOKEN)
                            {
                                Sym_Suiv();
                                Test_Symbole(ID_TOKEN, ID_ERR);
                                addID(TVAR);
                            };
                            Test_Symbole(PV_TOKEN, PV_ERR);
                            break;
        case BEGIN_TOKEN :  break;
        default :           ERREUR(CONST_VAR_BEGIN_ERR);
                            break;
    }
}

void INSTS()
{
    Test_Symbole(BEGIN_TOKEN,BEGIN_ERR);
    INST();
    while (SYM_COUR.CODE == PV_TOKEN)
    {
        Sym_Suiv();
        INST();
    }
    Test_Symbole(END_TOKEN,END_ERR);
}

void INST()
{
    switch(SYM_COUR.CODE)
    {
        case BEGIN_TOKEN :  INSTS();
                            break;
        case ID_TOKEN    :  AFFEC();
                            break;
        case IF_TOKEN    :  SI();
                            break;
        case WHILE_TOKEN :  TANTQUE();
                            break;
        case WRITE_TOKEN :  ECRIRE();
                            break;
        case READ_TOKEN  :  LIRE();
                            break;
        case END_TOKEN   :  break;
        case PV_TOKEN    :  break;
        case ELSE_TOKEN  :  break;
        case UNTIL_TOKEN :  break;
        case NUM_TOKEN   :  break;
        default          : ERREUR(INST_ERR);
    }

}

void AFFEC()
{
    Test_Symbole(ID_TOKEN,ID_ERR);
    semCheck(0);
    Test_Symbole(AFF_TOKEN,AFF_ERR);
    EXPR();
}

void SI()
{
    Test_Symbole(IF_TOKEN,IF_ERR);
    COND();
    Test_Symbole(THEN_TOKEN,THEN_ERR);
    INST();
}

void TANTQUE()
{
    Test_Symbole(WHILE_TOKEN,WHILE_ERR);
    COND();
    Test_Symbole(DO_TOKEN,DO_ERR);
    INST();
}

void ECRIRE()
{
    Test_Symbole(WRITE_TOKEN,WRITE_ERR);
    Test_Symbole(PO_TOKEN,PO_ERR);
    EXPR();
    Sym_Suiv();
    while(SYM_COUR.CODE == VIR_TOKEN)
    {
        Sym_Suiv();
        EXPR();
    }
    Test_Symbole(PF_TOKEN,PF_ERR);
}

void LIRE()
{
    Test_Symbole(READ_TOKEN,READ_ERR);
    Test_Symbole(PO_TOKEN,PO_ERR);
    Test_Symbole(ID_TOKEN,ID_ERR);
    semCheck(0);
    while( SYM_COUR.CODE == VIR_TOKEN)
    {
        Sym_Suiv();
        Test_Symbole(ID_TOKEN,ID_ERR);
        semCheck(0);

    }
    Test_Symbole(PF_TOKEN,PF_ERR);
}

void COND()
{
    EXPR();
    Sym_Suiv();
    switch(SYM_COUR.CODE)
    {
        case EG_TOKEN    : break;
        case DIFF_TOKEN  : break;
        case INF_TOKEN   : break;
        case SUP_TOKEN   : break;
        case INFEG_TOKEN : break;
        case SUPEG_TOKEN : break;
    }
    EXPR();
}

void EXPR()
{
    TERM();
    while(SYM_COUR.CODE == PLUS_TOKEN || SYM_COUR.CODE == MOINS_TOKEN)
    {
        Sym_Suiv();
        TERM();
    }
}

void TERM()
{
    FACT();
    while(SYM_COUR.CODE == MULT_TOKEN || SYM_COUR.CODE == DIV_TOKEN)
    {
        Sym_Suiv();
        FACT();
    }
}

void FACT()
{
    switch(SYM_COUR.CODE)
    {
        case ID_TOKEN : Sym_Suiv();
                        semCheck(1);
                        break;
        case NUM_TOKEN : Sym_Suiv();break;
        case PO_TOKEN : Sym_Suiv();
                        EXPR();
                        Test_Symbole(PF_TOKEN,PF_ERR);
                        break;
        default : ERREUR(FACT_ERR);
    }
}

void REPETER()
{
    Test_Symbole(REPEAT_TOKEN,REPEAT_ERR);
    INST();
    Test_Symbole(UNTIL_TOKEN,UNTIL_ERR);
    COND();
}

void POUR()
{
    Test_Symbole(FOR_TOKEN,FOR_ERR);
    Test_Symbole(ID_TOKEN,ID_ERR);
    semCheck(0);
    Test_Symbole(DO_TOKEN,DO_ERR);
    Test_Symbole(AFF_TOKEN,AFF_ERR);
    Test_Symbole(NUM_TOKEN,NUM_ERR);
    Sym_Suiv();
    switch(SYM_COUR.CODE)
    {
        case INTO_TOKEN : break;
        case DOWNTO_TOKEN : break;
        default: ERREUR(POUR_ERR);
    }
    Sym_Suiv();
    Test_Symbole(NUM_TOKEN,NUM_ERR);
    Test_Symbole(DO_TOKEN,DO_ERR);
    INST();
}

void CAS()
{
    Test_Symbole(CASE_TOKEN,CASE_ERR);
    Test_Symbole(ID_TOKEN,ID_ERR);
    semCheck(0);
    Test_Symbole(OF_TOKEN,OF_ERR);
    Test_Symbole(NUM_TOKEN,NUM_ERR);
    Test_Symbole(PTS_TOKEN,PTS_ERR);
    INST();
    Sym_Suiv();
    while(SYM_COUR.CODE == NUM_TOKEN)
    {
        Sym_Suiv();
        Test_Symbole(PTS_TOKEN,PTS_ERR);
        INST();
    }
    switch(SYM_COUR.CODE)
    {
        case ELSE_TOKEN : Sym_Suiv();
                          INST();
                          break;
        case END_TOKEN : Sym_Suiv();
                         break;
        default : ERREUR(CAS_ERR);
    }
}

void CONTROL(){
  switch(SYM_COUR.CODE)
  {
      case IF_TOKEN : Sym_Suiv();
                      IF();
                      break;
      case CASE_TOKEN : Sym_Suiv();
                        CASE();
                        break;
      default : ERREUR(CAS_ERR);
  }
}

void IF(){
  Test_Symbole(IF_TOKEN,IF_ERR);
  Test_Symbole(PO_TOKEN,PO_ERR);
  COND();
  Test_Symbole(PF_TOKEN,PF_ERR);
  INSTS();
  if(SYM_COUR.CODE == ELIF_TOKEN)){
    Sym_Suiv();
    INSTS();
    if(SYM_COUR.CODE == ELSE_TOKEN){
      Sym_Suiv();
      INSTS();
    }
  }
  if(SYM_COUR.CODE == ELSE_TOKEN){
    Sym_Suiv();
    INSTS();

}

void CASE(){
  Test_Symbole(SWITCH_TOKEN,SWITCH_ERR);
  Test_Symbole(PO_TOKEN,PO_ERR);
  Test_Symbole(NUM_TOKEN,NUM_ERR);
  Test_Symbole(PF_TOKEN,PF_ERR);
  BLOCK_CASE();
}

void BLOCK_CASE(){
  Test_Symbole(CASE_TOKEN,CASE_ERR);
  FACT();
  Test_Symbole(PTS_TOKEN,PTS_ERR);
  INSTS();
  while(SYM_COUR.CODE == CASE_TOKEN){
      Sym_Suiv();
      BLOCK_CASE();
  }
}


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
