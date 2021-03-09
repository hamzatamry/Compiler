#include <stdio.h>
#include <stdlib.h>
#include "syntabs.h"
#include "dico.h"
#include "util.h"

void parcours_n_prog(n_prog *n, int disp_tab, int disp_mips);
void parcours_l_instr(n_l_instr *n);
void parcours_instr(n_instr *n);
void parcours_instr_si(n_instr *n);
void parcours_instr_tantque(n_instr *n);
void parcours_instr_faire(n_instr *n);      /* MODIFIE POUR EVAL */
void parcours_instr_pour(n_instr *n);       /* MODIFIE POUR EVAL */
void parcours_instr_affect(n_instr *n);
void parcours_instr_appel(n_instr *n);
void parcours_instr_retour(n_instr *n);
void parcours_instr_ecrire(n_instr *n);
void parcours_l_exp(n_l_exp *n);
void parcours_exp(n_exp *n);
void parcours_varExp(n_exp *n);
void parcours_opExp(n_exp *n);
void parcours_intExp(n_exp *n);
void parcours_lireExp(n_exp *n);
void parcours_appelExp(n_exp *n);
void parcours_l_dec(n_l_dec *n);
void parcours_dec(n_dec *n);
void parcours_foncDec(n_dec *n);
void parcours_varDec(n_dec *n);
void parcours_tabDec(n_dec *n);
void parcours_var(n_var *n);
void parcours_var_simple(n_var *n);
void parcours_var_indicee(n_var *n);
void parcours_appel(n_appel *n);
int decLength(n_l_dec* item);
int expLength(n_l_exp* item);
int next_reg();

int contexte = C_VARIABLE_GLOBALE;
int adresseLocaleCourante;
int adresseArgumentCourant;
int adresseGlobaleCourant;
int reg = 0;
int etiquette = 1;
int nbSuiteSi = 1;
int nbSinon = 1;
int nbTest = 1;
int nbSuiteTantQue = 1;
int retourEffectue = 0;
int variableLocalePresente = 0;
int nbTestPour = 1;
int nbSuitePour = 1;
int nbCondExp = 1;
int nbSuiteCondExp = 1;

int afficher_mips = 0;
int afficher_dico = 0;

int decLength(n_l_dec* item)
{
  n_l_dec* cur = item;
  int size = 0;

  while (cur != NULL)
  {
    ++size;
    cur = cur->queue;
  }

  return size;
}

int expLength(n_l_exp* item)
{
  n_l_exp* cur = item;
  int size = 0;

  while (cur != NULL)
  {
    ++size;
    cur = cur->queue;
  }

  return size;
}

void empile(char *reg) {
  printf("\tsubi\t$sp, $sp, 4\t# Alloue un mot sur la pile\n");
  printf("\tsw\t%s, ($sp)\t# Copie reg vers sommet de pile\n", reg);
}

void depile(char *reg) {
  printf("\tlw\t%s, ($sp)\t# Copie sommet de pile vers reg\n", reg);
  printf("\taddi\t$sp, $sp, 4\t # Desaloue un mot sur la pile\n");
}

/*-------------------------------------------------------------------------*/

void parcours_n_prog(n_prog *n, int disp_tab, int disp_mips)
{
  int pos;

  afficher_dico = disp_tab;
  afficher_mips = disp_mips;

  if (afficher_mips) {
      printf("\t.data\n");
  }

  parcours_l_dec(n->variables);

  if (afficher_mips) {
      printf("\t.text\n__start:\n\tjal\tmain\n\tli\t$v0, 10\n\tsyscall\t\t# Stoppe l'exécution du processus\n");
  }

  parcours_l_dec(n->fonctions);

  if ((pos = rechercheExecutable("main")) == -1) {
      printf("Erreur : La fonction \"main\" n'est pas déclarée.\n");
      exit(-1);
  }

  if (dico.tab[pos].complement != 0) {
      printf("Erreur : La fonction \"main\" ne doit pas avoir d'arguments.\n");
      exit(-1);
  }

}

/*-------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------*/

void parcours_l_instr(n_l_instr *n)
{
  if(n){
    parcours_instr(n->tete);
    parcours_l_instr(n->queue);
  }
}

/*-------------------------------------------------------------------------*/

void parcours_instr(n_instr *n)
{
  if(n){
    if(n->type == blocInst) parcours_l_instr(n->u.liste);
    else if(n->type == affecteInst) parcours_instr_affect(n);
    else if(n->type == siInst) parcours_instr_si(n);
    else if(n->type == tantqueInst) parcours_instr_tantque(n);
    else if(n->type == faireInst) parcours_instr_faire(n);
    else if(n->type == pourInst) parcours_instr_pour(n);
    else if(n->type == appelInst) parcours_instr_appel(n);
    else if(n->type == retourInst) parcours_instr_retour(n);
    else if(n->type == ecrireInst) parcours_instr_ecrire(n);
  }
}

/*-------------------------------------------------------------------------*/

void parcours_instr_si(n_instr *n)
{
    parcours_exp(n->u.si_.test);

    if (afficher_mips) {
        /*nbSinon = nbSinon + 1;
        nbSuiteSi = nbSuiteSi + 1;*/
        if(n->u.si_.sinon) {
            depile("$t0");
            printf("\tbeq\t$t0, $zero, sinon%d\n", nbSinon);
        } else {
            depile("$t0");
            printf("\tbeq\t$t0, $zero, suiteSi%d\n", nbSuiteSi);
        }
    }

    parcours_instr(n->u.si_.alors);

    if(n->u.si_.sinon){
        if (afficher_mips) {
            printf("\tj\tsuiteSi%d\n", nbSuiteSi);
            printf("sinon%d:\n", nbSinon);
            nbSinon = nbSinon + 1;
        }
        parcours_instr(n->u.si_.sinon);
    }

    if (afficher_mips) {
        printf("suiteSi%d:\n", nbSuiteSi);
        nbSuiteSi = nbSuiteSi + 1;
    }
}

/*-------------------------------------------------------------------------*/

void parcours_instr_tantque(n_instr *n)
{

    if (afficher_mips) {
        nbTest = nbTest + 1;
        printf("test%d:\n", nbTest);
    }

    parcours_exp(n->u.tantque_.test);

    if (afficher_mips) {
        nbSuiteTantQue = nbSuiteTantQue + 1;
        depile("$t1");
        printf("\tbeq\t$t1, $zero, suiteTantQue%d\n", nbSuiteTantQue);
    }

    parcours_instr(n->u.tantque_.faire);

    if (afficher_mips) {
        printf("\tj\ttest%d\n", nbTest);
        nbTest = nbTest - 1;
        printf("suiteTantQue%d:\n", nbSuiteTantQue);
        nbSuiteTantQue = nbSuiteTantQue - 1;
    }

/* CODE TANT QUE IMBRIQUE
    if (afficher_mips) {
        printf("test%d:\n", nbTest);
    }

    parcours_exp(n->u.tantque_.test);

    if (afficher_mips) {
        depile("$t1");
        printf("\tbeq\t$t1, $zero, suiteTantQue%d\n", nbSuiteTantQue);
    }

    parcours_instr(n->u.tantque_.faire);

    if (afficher_mips) {
        printf("\tj\ttest%d\n", nbTest);
        nbTest = nbTest + 1;
        printf("suiteTantQue%d:\n", nbSuiteTantQue);
        nbSuiteTantQue = nbSuiteTantQue + 1;
    }*/
}

/*-------------------------------------------------------------------------*/

void parcours_instr_faire(n_instr *n)          /* MODIFIE POUR EVAL */
{                                             /* MODIFIE POUR EVAL */
  parcours_instr(n->u.faire_.faire);           /* MODIFIE POUR EVAL */
  parcours_exp(n->u.faire_.test);              /* MODIFIE POUR EVAL */
}                                             /* MODIFIE POUR EVAL */

/*-------------------------------------------------------------------------*/

void parcours_instr_pour(n_instr *n)                /* MODIFIE POUR EVAL */
{                                                  /* MODIFIE POUR EVAL */
    /* CODE POUR IMBRIQUE
    parcours_instr(n->u.pour_.init);

    if (afficher_mips) {
        nbTestPour = nbTestPour + 1;
        printf("testPour%d:\n", nbTestPour);
    }

    parcours_exp(n->u.tantque_.test);

    if (afficher_mips) {
        nbSuitePour = nbSuitePour + 1;
        depile("$t1");
        printf("\tbeq\t$t1, $zero, suitePour%d\n", nbSuitePour);
    }

    parcours_instr(n->u.tantque_.faire);
    parcours_instr(n->u.pour_.incr);

    if (afficher_mips) {
        printf("\tj\ttestPour%d\n", nbTestPour);
        nbTestPour = nbTestPour - 1;
        printf("suitePour%d:\n", nbSuitePour);
        nbSuitePour = nbSuitePour - 1;
    }
    */

    parcours_instr(n->u.pour_.init);                  /* MODIFIE POUR EVAL */

    if (afficher_mips) {
        printf("testPour%d:\n", nbTestPour);
    }

    parcours_exp(n->u.pour_.test);                    /* MODIFIE POUR EVAL */

    if (afficher_mips) {
        depile("$t1");
        printf("\tbeq\t$t1, $zero, suitePour%d\n", nbSuitePour);
    }

    parcours_instr(n->u.pour_.faire);                 /* MODIFIE POUR EVAL */
    parcours_instr(n->u.pour_.incr);                  /* MODIFIE POUR EVAL */

    if (afficher_mips) {
        printf("\tj\ttestPour%d\n", nbTestPour);
        nbTest = nbTest + 1;
        printf("suitePour%d:\n", nbSuitePour);
        nbSuiteTantQue = nbSuiteTantQue + 1;
    }
}                                                  /* MODIFIE POUR EVAL */

/*-------------------------------------------------------------------------*/

void parcours_instr_affect(n_instr *n)
{
    int pos;
    parcours_var(n->u.affecte_.var);
    parcours_exp(n->u.affecte_.exp);

    if (afficher_mips) {
      depile("$t1");

      if ((pos = rechercheExecutable(n->u.affecte_.var->nom)) != -1) {
        if(dico.tab[pos].classe == C_VARIABLE_GLOBALE) {
          printf("\tsw\t$t1, %s\n", n->u.affecte_.var->nom);
        }
        else if (dico.tab[pos].classe == C_VARIABLE_LOCALE) {
          printf("\tsw\t$t1, -%d($fp)\n", 8 + dico.tab[pos].adresse);
        }

      }

    }
}

/*-------------------------------------------------------------------------*/

void parcours_instr_appel(n_instr *n)
{
  parcours_appel(n->u.appel);
}

/*-------------------------------------------------------------------------*/

void parcours_appel(n_appel *n)
{

    int pos;


    if ((pos = rechercheExecutable(n->fonction)) != -1) {

      if (afficher_mips) {
          printf("\tsubi\t$sp, $sp, 4\t# Allocation de la valeur de retour\n");
      }

      if (expLength(n->args) != dico.tab[pos].complement) {
          printf("Erreur : Nombre d'arguments invalides pour la fonction \"%s\".\n", n->fonction);
          exit(-1);
      }

      if (afficher_mips) {
          printf("\t\t\t\t#Empile args\n");
      }

      parcours_l_exp(n->args);

      if (afficher_mips) {
          printf("\tjal\t%s\n", n->fonction);
           printf("\taddi\t$sp, $sp, %d\t# Desallocation param\n", dico.tab[pos].complement*4);
      }

      return;

    } else {
        printf("Erreur : La fonction \"%s\" n'est pas déclarée.\n", n->fonction);
        exit(-1);
    }
}

/*-------------------------------------------------------------------------*/

void parcours_instr_retour(n_instr *n)
{
  parcours_exp(n->u.retour_.expression);

  if (afficher_mips) {
      int nbArg = adresseArgumentCourant / 4;
      depile("$t0");
      printf("\tsw\t$t0, %d($fp)\t# Ecriture de la valeur de retour\n", 4 * (nbArg + 1));

      depile("$ra");
      depile("$fp");
      printf("\tjr\t$ra\n");

      retourEffectue = 1;
  }
}

/*-------------------------------------------------------------------------*/

void parcours_instr_ecrire(n_instr *n)
{
  parcours_exp(n->u.ecrire_.expression);

  if (afficher_mips) {
      depile("$a0");
      printf("\tli\t$v0, 1\n\tsyscall\t\t\t# Ecriture\n");
      printf("\tli\t$a0, '\\n'\n");
      printf("\tli\t$v0, 11\n");
      printf("\tsyscall\t\t\t# Ecriture char\n");
  }
}

/*-------------------------------------------------------------------------*/

void parcours_l_exp(n_l_exp *n)
{

  if(n){
    parcours_exp(n->tete);
    parcours_l_exp(n->queue);
  }
}

/*-------------------------------------------------------------------------*/

void parcours_exp(n_exp *n)
{
    int pos;

    if(n->type == varExp) {

        parcours_varExp(n);

        if (afficher_mips) {
          if((pos = rechercheExecutable(n->u.var->nom)) != -1) {
            if(dico.tab[pos].classe == C_VARIABLE_GLOBALE) {
              printf("\tlw\t$t1, %s\t\t# Lit la variable dans $t1\n", n->u.var->nom);
              empile("$t1");
            } else if (dico.tab[pos].classe == C_ARGUMENT) {
              printf("\tlw\t$t1, %d($fp)\t\t# Lit la variable dans $t1\n", 8 - dico.tab[pos].adresse); // TODO : a modifier, formule juste 4*nbargument - adresse
              empile("$t1");
            } else if (dico.tab[pos].classe == C_VARIABLE_LOCALE) {
              printf("\tlw\t$t1, -%d($fp)\t\t# Lit la variable dans $t1\n", 8 + dico.tab[pos].adresse); // TODO : a modifier, formule juste 4*nbargument - adresse
              empile("$t1");
            }
          }
        }


    } else if(n->type == opExp) {

        parcours_opExp(n);

        if (afficher_mips) {

            depile("$t1");
            depile("$t0");
            switch (n->u.opExp_.op) {

                case plus:
                    printf("\tadd\t$t2, $t0, $t1\n");
                    empile("$t2");
                    break;

                case moins:
                    printf("\tsub\t$t2, $t0, $t1\n");
                    empile("$t2");
                    break;

                case fois:
                    printf("\tmult\t$t0, $t1\n");
                    printf("\tmflo\t$t2\n");
                    empile("$t2");
                    break;

                case divise:
                    printf("\tdiv\t$t0, $t1\n");
                    printf("\tmflo\t$t2\n");
                    empile("$t2");
                    break;

                case modulo:
                    printf("\tdiv\t$t0, $t1\n");
                    printf("\tmfhi\t$t2\n");
                    empile("$t2");
                    break;

                case egal:
                    printf("\tli\t$t2, -1\n");
                    printf("\tbeq\t$t0, $t1, e%d\t# Egal\n", etiquette);
                    printf("\tli\t$t2, 0\n");
                    printf("e%d:\n", etiquette);
                    empile("$t2");
                    etiquette = etiquette + 1;
                    break;

                case diff:
                    printf("\tli\t$t2, -1\n");
                    printf("\tbne\t$t0, $t1, e%d\t# Different\n", etiquette);
                    printf("\tli\t$t2, 0\n");
                    printf("e%d:\n", etiquette);
                    empile("$t2");
                    etiquette = etiquette + 1;
                    break;

                case inf:
                    printf("\tli\t$t2, -1\n");
                    printf("\tblt\t$t0, $t1, e%d\t# Inferieur\n", etiquette);
                    printf("\tli\t$t2, 0\n");
                    printf("e%d:\n", etiquette);
                    empile("$t2");
                    etiquette = etiquette + 1;
                    break;

                case sup:
                    printf("\tli\t$t2, -1\n");
                    printf("\tbgt\t$t0, $t1, e%d\t# Superieur\n", etiquette);
                    printf("\tli\t$t2, 0\n");
                    printf("e%d:\n", etiquette);
                    empile("$t2");
                    etiquette = etiquette + 1;
                    break;

                case ou:
                    printf("\tor\t$t2, $t0, $t1\n");
                    empile("$t2");
                    break;

                case et:
                    printf("\tand\t$t2, $t0, $t1\n");
                    empile("$t2");
                    break;

                case non:
                    printf("\tnot\t$t2, $t0\n");
                    empile("$t2");
                    break;

                case infeg:
                    printf("\tli\t$t2, -1\n");
                    printf("\tble\t$t0, $t1, e%d\t# Inferieur ou egal\n", etiquette);
                    printf("\tli\t$t2, 0\n");
                    printf("e%d:\n", etiquette);
                    empile("$t2");
                    etiquette = etiquette + 1;
                    break;

                case supeg:
                    printf("\tli\t$t2, -1\n");
                    printf("\tbge\t$t0, $t1, e%d\t# Superieur ou egal\n", etiquette);
                    printf("\tli\t$t2, 0\n");
                    printf("e%d:\n", etiquette);
                    empile("$t2");
                    etiquette = etiquette + 1;
                    break;

                case negatif:
                    break;

                case tern:

                    parcours_exp(n->u.opExp_.op1);

                    printf("\tbeq\t$t0, $zero, condexp%d\n", nbCondExp);

                    parcours_exp(n->u.opExp_.op2);

                    printf("\tj\tsuiteCondExp%d\n", nbCondExp);
                    printf("condexp%d:\n", nbCondExp);
                    nbCondExp = nbCondExp + 1;

                    parcours_exp(n->u.opExp_.op3);

                    printf("suiteCondExp%d:\n", nbSuiteCondExp);
                    nbSuiteCondExp = nbSuiteCondExp + 1;

                    break;
            }

        }

    } else if(n->type == intExp) {

        parcours_intExp(n);

        if (afficher_mips) {

            printf("\tli\t$t0, %d\t# Place l'entier dans le registre\n", n->u.entier);
            empile("$t0");
        }

    } else if(n->type == appelExp) {

        parcours_appelExp(n);



    } else if(n->type == lireExp) {

        parcours_lireExp(n);

        if (afficher_mips) {

            printf("\tli $v0, 5\n");
            printf("\tsyscall\t\t\t\t# Lire\n");
            empile("$v0");
        }
    }
}

/*-------------------------------------------------------------------------*/

void parcours_varExp(n_exp *n)
{
  parcours_var(n->u.var);
}

/*-------------------------------------------------------------------------*/
void parcours_opExp(n_exp *n)
{
  if( n->u.opExp_.op1 != NULL ) {
    parcours_exp(n->u.opExp_.op1);
  }
  if( n->u.opExp_.op2 != NULL ) {
    parcours_exp(n->u.opExp_.op2);
  }
}

/*-------------------------------------------------------------------------*/

void parcours_intExp(n_exp *n)
{

}

/*-------------------------------------------------------------------------*/
void parcours_lireExp(n_exp *n)
{

}

/*-------------------------------------------------------------------------*/

void parcours_appelExp(n_exp *n)
{
  parcours_appel(n->u.appel);
}

/*-------------------------------------------------------------------------*/

void parcours_l_dec(n_l_dec *n)
{
  if( n ){
    parcours_dec(n->tete);
    parcours_l_dec(n->queue);
  }
}

/*-------------------------------------------------------------------------*/

void parcours_dec(n_dec *n)
{

  if(n){
    if(n->type == foncDec) {
      parcours_foncDec(n);
    }
    else if(n->type == varDec) {
      parcours_varDec(n);
    }
    else if(n->type == tabDec) {
      parcours_tabDec(n);
    }
  }
}


/*-------------------------------------------------------------------------*/

void parcours_foncDec(n_dec *n)
{

    if (rechercheDeclarative(n->nom) == -1) {
        ajouteIdentificateur(n->nom, C_VARIABLE_GLOBALE, T_FONCTION, 0, decLength(n->u.foncDec_.param));

        entreeFonction();

        if (afficher_mips) {
          printf("%s:\n", n->nom);
          empile("$fp");
          printf("\tmove\t$fp, $sp\n");
          empile("$ra");
        }

        contexte = C_ARGUMENT;
        parcours_l_dec(n->u.foncDec_.param);
        contexte = C_VARIABLE_LOCALE;

        parcours_l_dec(n->u.foncDec_.variables);
        parcours_instr(n->u.foncDec_.corps);

        if (afficher_dico) {
          affiche_dico();
        }


        if(variableLocalePresente == 1) {
            if (afficher_mips) {
                printf("\taddi\t$sp, $sp, %d\t# Desallocation variable locale\n", adresseLocaleCourante);
            }
        }

        if (afficher_mips && (retourEffectue == 0)) {
            depile("$ra");
            depile("$fp");
            printf("\tjr\t$ra\n");
        }

        retourEffectue = 0;
        variableLocalePresente = 0;


        sortieFonction();

        return;

    } else {
        printf("Erreur : La fonction \"%s\" est déjà déclarée.\n", n->nom);
        exit(-1);
    }
}

/*-------------------------------------------------------------------------*/

void parcours_varDec(n_dec *n)
{
    if (rechercheDeclarative(n->nom) == -1) {

        switch (contexte) {
            case C_VARIABLE_GLOBALE:
                ajouteIdentificateur(n->nom, contexte, T_ENTIER, adresseGlobaleCourant, -1);
                adresseGlobaleCourant += 4;
                if (afficher_mips) {
                  printf("%s:\t.space\t4\n", n->nom);
                }
                break;
            case C_VARIABLE_LOCALE:
                ajouteIdentificateur(n->nom, contexte, T_ENTIER, adresseLocaleCourante, -1);
                adresseLocaleCourante += 4;
                variableLocalePresente = 1;
                if (afficher_mips) {
                    printf("\tsubi\t$sp, $sp 4\t# Allocation variable locale\n");
                }
                break;
            case C_ARGUMENT:
                ajouteIdentificateur(n->nom, contexte, T_ENTIER, adresseArgumentCourant, -1);
                adresseArgumentCourant += 4;
                break;
        }

        return;

    } else {

      printf("Erreur : La variable \"%s\" déjà déclarée.\n", n->nom);
      exit(-1);
    }
}

/*-------------------------------------------------------------------------*/

void parcours_tabDec(n_dec *n)
{
    if (rechercheDeclarative(n->nom) == -1) {
        ajouteIdentificateur(n->nom, C_VARIABLE_GLOBALE, T_TABLEAU_ENTIER, dico.sommet, n->u.tabDec_.taille);

        if (afficher_mips) {
          printf("%s:\t.space\t%d\n", n->nom, 4 * n->u.tabDec_.taille);
        }

        return;
    } else {
        printf("Erreur : Le tableau \"%s\" est déjà déclaré.\n", n->nom);
        exit(-1);
    }
}

/*-------------------------------------------------------------------------*/

void parcours_var(n_var *n)
{
  if(n->type == simple) {
    parcours_var_simple(n);
  }
  else if(n->type == indicee) {
    parcours_var_indicee(n);
  }
}

/*-------------------------------------------------------------------------*/
void parcours_var_simple(n_var *n)
{
    int pos;

    if ((pos = rechercheExecutable(n->nom)) != -1) {

      if (dico.tab[pos].type != T_ENTIER) {
        printf("Erreur : Le type de la variable \"%s\" est incorrect. Variable de type \"ENTIER\" attendue.\n", n->nom);
        exit(-1);
      }

      return;

    } else {
      printf("Erreur : La variable \"%s\" n'est pas déclarée.\n", n->nom);
      exit(-1);
    }
}

/*-------------------------------------------------------------------------*/
void parcours_var_indicee(n_var *n)
{
    int pos;

    if ((pos = rechercheExecutable(n->nom)) != -1) {

      if (dico.tab[pos].type != T_TABLEAU_ENTIER) {
        printf("Erreur : Le tableau \"%s\" est déclaré comme une variable de type \"ENTIER\".\n", n->nom);
        exit(-1);
      }

      parcours_exp( n->u.indicee_.indice );

      if (afficher_mips) {
          printf("\tlw\t$t1, %d(%s)\t\t# Lit la variable dans $t1\n", n->u.indicee_.indice->u.entier, n->nom);
          empile("$t1");
      }
      return;

    } else {
      printf("Erreur : Le tableau \"%s\" n'est pas déclaré.\n", n->nom);
      exit(-1);
    }
}
/*-------------------------------------------------------------------------*/
