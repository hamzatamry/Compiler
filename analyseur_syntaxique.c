#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "analyseur_syntaxique.h"
#include "analyseur_lexical.h"
#include "util.h"
#include "symboles.h"
#include "premiers.h"
#include "suivants.h"
#include "syntabs.h"
#include "affiche_arbre_abstrait.h"
#include "generation_code.h"

int uniteCourante;
int afficher_synt = 0;

/************* AFFICHER SYMBOLES *************/
void afficher_element(int unite) {
	char *fct = malloc(99 * sizeof(char));
	char *val = malloc(99 * sizeof(char));

	nom_token(unite, fct, val);
	affiche_element(fct, val, afficher_synt);
}
/*********************************************/

/************* RECUPERER VALEUR *************/
char *recuperer_valeur(int unite) {
	char *fct = malloc(99 * sizeof(char));
	char *val = malloc(99 * sizeof(char));

	nom_token(unite, fct, val);
	return val;
}
/*********************************************/

n_prog *programme(int disp_synt) {

	afficher_synt = disp_synt;

	n_l_dec *$1 = NULL;
	n_l_dec *$2 = NULL;
	n_prog *$$ = NULL;

	affiche_balise_ouvrante("programme", afficher_synt);
	if (est_premier(uniteCourante, _optDecVariables_) || est_premier(uniteCourante,_listeDecFonctions_) || est_suivant(uniteCourante, _programme_)) {
		$1 = optDecVariables();
		$2 = listeDecFonctions();
		$$ = cree_n_prog($1, $2);
	} else {
		erreur("erreur de syntaxe -> \'ENTIER\' ou identifiant de fonction attendu.");
	}

	affiche_balise_fermante("programme", afficher_synt);
	return $$;
}




n_l_dec *optDecVariables() {
	n_l_dec *$$ = NULL;

	affiche_balise_ouvrante("optDecVariables", afficher_synt);

	if (est_premier(uniteCourante, _listeDecVariables_)) {
		$$ = listeDecVariables();
		if (uniteCourante == POINT_VIRGULE) {
			afficher_element(uniteCourante);
			uniteCourante = yylex();
		} else {
			erreur("erreur de syntaxe -> \';\' attendu.");
		}
	} else if (est_suivant(uniteCourante, _optDecVariables_)) {
		/* RIEN */
	} else {
		erreur("erreur de syntaxe -> \'ENTIER\' attendu.");
	}

	affiche_balise_fermante("optDecVariables", afficher_synt);
	return $$;
}




n_l_dec *listeDecVariables() {
	n_dec *$1 = NULL;
	n_l_dec *$2 = NULL;
	n_l_dec *$$ = NULL;

	affiche_balise_ouvrante("listeDecVariables", afficher_synt);

	if (est_premier(uniteCourante, _declarationVariable_)) {
		$1 = declarationVariable();
		$2 = listeDecVariablesBis($$);
		$$ = cree_n_l_dec($1, $2);
	} else {
		erreur("erreur de syntaxe -> \'ENTIER\' attendu.");
	}

	affiche_balise_fermante("listeDecVariables", afficher_synt);
	return $$;
}




n_l_dec *listeDecVariablesBis(n_l_dec *herite) {
	n_dec *$2 = NULL;
	n_l_dec *$$ = NULL;
	n_l_dec *herite_fils = NULL;

	affiche_balise_ouvrante("listeDecVariablesBis", afficher_synt);

	if (uniteCourante == VIRGULE) {
		afficher_element(uniteCourante);
		uniteCourante = yylex();
		$2 = declarationVariable();
		herite_fils = listeDecVariablesBis(herite);
		$$ = cree_n_l_dec($2, herite_fils);
	} else if (est_suivant(uniteCourante, _listeDecVariablesBis_)) {
		$$ = herite;
	} else {
		erreur("erreur de syntaxe -> \',\' attendue.");
	}

	affiche_balise_fermante("listeDecVariablesBis", afficher_synt);
	return $$;
}




n_dec *declarationVariable() {
	n_dec *$$ = NULL;
	char *nom;
	int tailleTableau = 0;

	affiche_balise_ouvrante("declarationVariable", afficher_synt);

	if (uniteCourante == ENTIER) {
		afficher_element(uniteCourante);
		uniteCourante = yylex();
		if (uniteCourante == ID_VAR) {
			// Récupération du nom
			nom = recuperer_valeur(uniteCourante);
			afficher_element(uniteCourante);
			uniteCourante = yylex();
			tailleTableau = optTailleTableau();
			if (tailleTableau == -1) {
				$$ = cree_n_dec_var(nom);
			} else {
				$$ = cree_n_dec_tab(nom, tailleTableau);
			}
		} else {
			erreur("erreur de syntaxe -> identifiant de variable attendu.");
		}
	} else {
		erreur("erreur de syntaxe -> \'ENTIER\' attendu.");
	}

	affiche_balise_fermante("declarationVariable", afficher_synt);
	return $$;
}




int optTailleTableau() {
	// Taille du tableau à -1 par défaut
	int taille = -1;

	affiche_balise_ouvrante("optTailleTableau", afficher_synt);

	if (uniteCourante == CROCHET_OUVRANT) {
		afficher_element(uniteCourante);
		uniteCourante = yylex();
		if (uniteCourante == NOMBRE) {
			// Récupération et conversion de la taille du tableau
			taille = atoi(recuperer_valeur(uniteCourante));
			afficher_element(uniteCourante);
			uniteCourante = yylex();
			if (uniteCourante == CROCHET_FERMANT) {
				afficher_element(uniteCourante);
				uniteCourante = yylex();
			} else {
				erreur("erreur de syntaxe -> \']\' attendu.");
			}
		} else {
			erreur("erreur de syntaxe -> nombre attendue");
		}
	} else if (est_suivant(uniteCourante, _optTailleTableau_)) {
		/* RIEN */
	} else {
		erreur("erreur de syntaxe -> \'[\' attendu.");
	}

	affiche_balise_fermante("optTailleTableau", afficher_synt);
	return taille;
}




n_l_dec *listeDecFonctions() {
	n_dec *$1 = NULL;
	n_l_dec *$2 = NULL;
	n_l_dec *$$ = NULL;

	affiche_balise_ouvrante("listeDecFonctions", afficher_synt);

	if (est_premier(uniteCourante, _declarationFonction_)) {
		$1 = declarationFonction();
		$2 = listeDecFonctions();
		$$ = cree_n_l_dec($1, $2);
	} else if (est_suivant(uniteCourante, _listeDecFonctions_)) {
		/* RIEN */
	} else {
		erreur("erreur de syntaxe -> identifiant de fonction attendu.");
	}

	affiche_balise_fermante("listeDecFonctions", afficher_synt);
	return $$;
}




n_dec *declarationFonction() {
	n_l_dec *$2 = NULL;
	n_l_dec *$3 = NULL;
	n_instr *$4 = NULL;
	n_dec *$$ = NULL;
	char *nom;

	affiche_balise_ouvrante("declarationFonction", afficher_synt);

	if (uniteCourante == ID_FCT) {
		// Récupération du nom de la fonction
		nom = recuperer_valeur(uniteCourante);
		afficher_element(uniteCourante);
		uniteCourante = yylex();
		$2 = listeParam();
		$3 = optDecVariables();
		$4 = instructionBloc();
		$$ = cree_n_dec_fonc(nom, $2, $3, $4);
	} else {
		erreur("erreur de syntaxe -> identifiant de fonction attendu.");
	}

	affiche_balise_fermante("declarationFonction", afficher_synt);
	return $$;
}




n_l_dec *listeParam() {
	n_l_dec *$$ = NULL;

	affiche_balise_ouvrante("listeParam", afficher_synt);

	if (uniteCourante == PARENTHESE_OUVRANTE) {
		afficher_element(uniteCourante);
		uniteCourante = yylex();
		$$ = optListeDecVariables();
		if (uniteCourante == PARENTHESE_FERMANTE) {
			afficher_element(uniteCourante);
			uniteCourante = yylex();
		} else {
			erreur("erreur de syntaxe -> \')\' attendue.");
		}
	} else {
		erreur("erreur de syntaxe -> \'(\' attendue.");
	}

	affiche_balise_fermante("listeParam", afficher_synt);
	return $$;
}




n_l_dec *optListeDecVariables() {
	n_l_dec *$$ = NULL;

	affiche_balise_ouvrante("optListeDecVariables", afficher_synt);

	if (est_premier(uniteCourante, _listeDecVariables_)) {
		$$ = listeDecVariables();
	} else if (est_suivant(uniteCourante, _optListeDecVariables_)) {
		/* RIEN */
	} else {
		erreur("erreur de syntaxe -> \'ENTIER\' attendu.");
	}

	affiche_balise_fermante("optListeDecVariables", afficher_synt);
	return $$;
}




n_instr *instruction() {
	n_instr *$$ = NULL;

	affiche_balise_ouvrante("instruction", afficher_synt);

	if (est_premier(uniteCourante, _instructionAffect_)) {
		$$ = instructionAffect();
	} else if (est_premier(uniteCourante, _instructionBloc_)) {
		$$ = instructionBloc();
	} else if (est_premier(uniteCourante, _instructionSi_)) {
		$$ = instructionSi();
	} else if (est_premier(uniteCourante, _instructionTantque_)) {
		$$ = instructionTantque();
	} else if (est_premier(uniteCourante, _instructionAppel_)) {
		$$ = instructionAppel();
	} else if (est_premier(uniteCourante, _instructionRetour_)) {
		$$ = instructionRetour();
	} else if (est_premier(uniteCourante, _instructionEcriture_)) {
		$$ = instructionEcriture();
	} else if (est_premier(uniteCourante, _instructionVide_)) {
		$$ = instructionVide();
	} else if (est_premier(uniteCourante, _instructionPour_)) {
		$$ = instructionPour();
	} else {
		erreur("erreur de syntaxe -> symbole ou identifiant attendu.");
	}

	affiche_balise_fermante("instruction", afficher_synt);
	return $$;
}




n_instr *instructionAffect() {
	n_var *$1 = NULL;
	n_exp *$3 = NULL;
	n_instr *$$ = NULL;


	affiche_balise_ouvrante("instructionAffect", afficher_synt);

	if (est_premier(uniteCourante, _var_)) {
		$1 = var();
		if (uniteCourante == EGAL) {
			afficher_element(uniteCourante);
			uniteCourante = yylex();
			$3 = expression();
			if (uniteCourante == POINT_VIRGULE) {
				afficher_element(uniteCourante);
				uniteCourante = yylex();
				$$ = cree_n_instr_affect($1, $3);
			} else {
				erreur("erreur de syntaxe -> \';\' attendu.");
			}
		} else {
			erreur("erreur de syntaxe -> \'=\' attendu.");
		}
	} else {
		erreur("erreur de syntaxe -> identifiant de variable attendu.");
	}

	affiche_balise_fermante("instructionAffect", afficher_synt);
	return $$;
}




n_instr *instructionBloc() {
	n_l_instr *$2 = NULL;
	n_instr *$$ = NULL;

	affiche_balise_ouvrante("instructionBloc", afficher_synt);

	if (uniteCourante == ACCOLADE_OUVRANTE) {
		afficher_element(uniteCourante);
		uniteCourante = yylex();
		$2 = listeInstructions();
		if (uniteCourante == ACCOLADE_FERMANTE) {
			afficher_element(uniteCourante);
			uniteCourante = yylex();
			$$ = cree_n_instr_bloc($2);
		} else {
			erreur("erreur de syntaxe -> \'}\' attendu.");
		}
	} else {
		erreur("erreur de syntaxe -> \'{\' attendu.");
	}

	affiche_balise_fermante("instructionBloc", afficher_synt);
	return $$;
}


n_instr *instructionPour() {
	n_instr *$2 = NULL;
	n_exp *$3 = NULL;
	n_instr *$4 = NULL;
	n_instr *$6 = NULL;
	n_instr *$$ = NULL;

	affiche_balise_ouvrante("instructionPour", afficher_synt);

	if (uniteCourante == POUR) {
		afficher_element(uniteCourante);
		uniteCourante = yylex();
		$2 = instructionAffect();
		$3 = expression();
		if (uniteCourante == POINT_VIRGULE) {
			afficher_element(uniteCourante);
			uniteCourante = yylex();
			$4 = instructionAffect();
			if (uniteCourante == FAIRE) {
				afficher_element(uniteCourante);
				uniteCourante = yylex();
				$6 = instructionBloc();
				$$ = cree_n_instr_pour($2, $3, $4, $6);
			} else {
				erreur("erreur de syntaxe -> \'FAIRE\' attendu.");
			}
		} else {
			erreur("erreur de syntaxe -> \';\' attendu.");
		}
	} else {
		erreur("erreur de syntaxe -> \'POUR\' attendu.");
	}

	affiche_balise_fermante("instructionPour", afficher_synt);
	return $$;
}




n_l_instr *listeInstructions() {
	n_instr *$1 = NULL;
	n_l_instr *$2 = NULL;
	n_l_instr *$$ = NULL;

	affiche_balise_ouvrante("listeInstructions", afficher_synt);

	if (est_premier(uniteCourante, _instruction_)) {
		$1 = instruction();
		$2 = listeInstructions();
		$$ = cree_n_l_instr($1, $2);
	} else if (est_suivant(uniteCourante, _listeInstructions_)) {
		/* RIEN */
	} else {
		erreur("erreur de syntaxe -> symbole ou identifiant attendu.");
	}

	affiche_balise_fermante("listeInstructions", afficher_synt);
	return $$;
}




n_instr *instructionSi() {
	n_exp *$2 = NULL;
	n_instr *$4 = NULL;
	n_instr *$5 = NULL;
	n_instr *$$ = NULL;

	affiche_balise_ouvrante("instructionSi", afficher_synt);

	if (uniteCourante == SI) {
		afficher_element(uniteCourante);
		uniteCourante = yylex();
		$2 = expression();
		if (uniteCourante == ALORS) {
			afficher_element(uniteCourante);
			uniteCourante = yylex();
			$4 = instructionBloc();
			$5 = optSinon();
			$$ = cree_n_instr_si($2, $4, $5);
		} else {
			erreur("erreur de syntaxe -> \'ALORS\' attendu.");
		}
	} else {
		erreur("erreur de syntaxe -> \'SI\' attendu.");
	}

	affiche_balise_fermante("instructionSi", afficher_synt);
	return $$;
}




n_instr *optSinon() {
	n_instr *$$ = NULL;

	affiche_balise_ouvrante("optSinon", afficher_synt);

	if (uniteCourante == SINON) {
		afficher_element(uniteCourante);
		uniteCourante = yylex();
	  	$$ = instructionBloc();
	} else if (est_suivant(uniteCourante, _optSinon_)) {
		/* RIEN */
	} else {
		erreur("erreur de syntaxe -> \'SINON\' attendu.");
	}

	affiche_balise_fermante("optSinon", afficher_synt);
	return $$;
}




n_instr *instructionTantque() {
	n_exp *$2 = NULL;
	n_instr *$4 = NULL;
	n_instr *$$ = NULL;

	affiche_balise_ouvrante("instructionTantque", afficher_synt);

	if (uniteCourante == TANTQUE) {
		afficher_element(uniteCourante);
		uniteCourante = yylex();
		$2 = expression();
		if (uniteCourante == FAIRE) {
			afficher_element(uniteCourante);
			uniteCourante = yylex();
			$4 = instructionBloc();
			$$ = cree_n_instr_tantque($2, $4);
		} else {
			erreur("erreur de syntaxe -> \'FAIRE\' attendu.");
		}
	} else {
		erreur("erreur de syntaxe -> \'TANTQUE\' attendu.");
	}

	affiche_balise_fermante("instructionTantque", afficher_synt);
	return $$;
}




n_instr *instructionAppel() {
	n_appel *$1 = NULL;
	n_instr *$$ = NULL;

	affiche_balise_ouvrante("instructionAppel", afficher_synt);

	if (est_premier(uniteCourante, _appelFct_)) {
		$1 = appelFct();
		if (uniteCourante == POINT_VIRGULE) {
			afficher_element(uniteCourante);
			uniteCourante = yylex();
			$$ = cree_n_instr_appel($1);
		} else {
			erreur("erreur de syntaxe -> \';\' attendu.");
		}
	} else {
		erreur("erreur de syntaxe -> identifiant de fonction attendu.");
	}

	affiche_balise_fermante("instructionAppel", afficher_synt);
	return $$;
}




n_instr *instructionRetour() {
	n_exp *$2 = NULL;
	n_instr *$$ = NULL;

	affiche_balise_ouvrante("instructionRetour", afficher_synt);

	if (uniteCourante == RETOUR) {
		afficher_element(uniteCourante);
		uniteCourante = yylex();
		$2 = expression();
		if (uniteCourante == POINT_VIRGULE) {
			afficher_element(uniteCourante);
			uniteCourante = yylex();
			$$ = cree_n_instr_retour($2);
		} else {
			erreur("erreur de syntaxe -> \';\' attendu.");
		}
	} else {
		erreur("erreur de syntaxe -> \'RETOUR\' attendu.");
	}

	affiche_balise_fermante("instructionRetour", afficher_synt);
	return $$;
}




n_instr *instructionEcriture() {
	n_exp *$3 = NULL;
	n_instr *$$ = NULL;

	affiche_balise_ouvrante("instructionEcriture", afficher_synt);

	if (uniteCourante == ECRIRE) {
		afficher_element(uniteCourante);
		uniteCourante = yylex();
		if (uniteCourante == PARENTHESE_OUVRANTE) {
			afficher_element(uniteCourante);
			uniteCourante = yylex();
			$3 = expression();
			if (uniteCourante == PARENTHESE_FERMANTE) {
				afficher_element(uniteCourante);
				uniteCourante = yylex();
				if (uniteCourante == POINT_VIRGULE) {
					afficher_element(uniteCourante);
					uniteCourante = yylex();
					$$ = cree_n_instr_ecrire($3);
				} else {
					erreur("erreur de syntaxe -> \';\' attendu.");
				}
			} else {
				erreur("erreur de syntaxe -> \'(\' attendue.");
			}
		} else {
			erreur("erreur de syntaxe -> \')\' attendue.");
		}
	} else {
		erreur("erreur de syntaxe -> \'ECRIRE\' attendu.");
	}

	affiche_balise_fermante("instructionEcriture", afficher_synt);
	return $$;
}




n_instr *instructionVide() {
	n_instr *$$ = NULL;

	affiche_balise_ouvrante("instructionVide", afficher_synt);

	if (uniteCourante == POINT_VIRGULE) {
		afficher_element(uniteCourante);
		uniteCourante = yylex();
		$$ = cree_n_instr_vide();
	} else {
		erreur("erreur de syntaxe -> \';\' attendu.");
	}

	affiche_balise_fermante("instructionVide", afficher_synt);
	return $$;
}




n_exp *condition() {
	n_exp *$1 = NULL;
	n_exp *$$ = NULL;

	affiche_balise_ouvrante("condition", afficher_synt);

	if (est_premier(uniteCourante, _conjonction_)) {
		$1 = conjonction();
		$$ = conditionBis($1);
	} else {
		erreur("erreur de syntaxe -> symbole ou identifiant attendu.");
	}

	affiche_balise_fermante("condition", afficher_synt);
	return $$;
}




n_exp *conditionBis(n_exp *herite) {
	n_exp *$2 = NULL;
	n_exp *herite_fils = NULL;
	n_exp *$$ = NULL;

	affiche_balise_ouvrante("conditionBis", afficher_synt);

	if (uniteCourante == OU) {
		afficher_element(uniteCourante);
		uniteCourante = yylex();
		$2 = conjonction();
		herite_fils = conditionBis(herite);
		$$ = cree_n_exp_op(ou, herite_fils, $2, NULL);
	} else if (est_suivant(uniteCourante, _conditionBis_)) {
		$$ = herite;
	} else {
		erreur("erreur de syntaxe -> \'|\' attendu.");
	}

	affiche_balise_fermante("conditionBis", afficher_synt);
	return $$;
}

n_exp *expression() {
	n_exp *$1 = NULL;
	n_exp *$$ = NULL;

	affiche_balise_ouvrante("expression", afficher_synt);

	if (est_premier(uniteCourante, _condition_)) {
		$1 = condition();
		$$ = expressionBis($1);
	} else {
		erreur("erreur de syntaxe -> symbole ou identifiant attendu.");
	}

	affiche_balise_fermante("expression", afficher_synt);
	return $$;
}




n_exp *expressionBis(n_exp *herite) {
	n_exp *$2 = NULL;
	n_exp *$3 = NULL;
	n_exp *herite_fils = NULL;
	n_exp *$$ = NULL;

	affiche_balise_ouvrante("expressionBis", afficher_synt);

	if (uniteCourante == INTERROGATION) {
		afficher_element(uniteCourante);
		uniteCourante = yylex();
		$2 = expression();

		if (uniteCourante == DEUXPOINTS) {
			afficher_element(uniteCourante);
			uniteCourante = yylex();
			$3 = expression();

			herite_fils = expressionBis(herite);
			$$ = cree_n_exp_op(tern, herite_fils, $2, $3);
		}

	} else if (est_suivant(uniteCourante, _expressionBis_)) {
		$$ = herite;
	} else {
		erreur("erreur de syntaxe -> \'?\' attendu.");
	}

	affiche_balise_fermante("expressionBis", afficher_synt);
	return $$;
}




n_exp *conjonction() {
	n_exp *$1 = NULL;
	n_exp *$$ = NULL;

	affiche_balise_ouvrante("conjonction", afficher_synt);

	if (est_premier(uniteCourante, _negation_)) {
		$1 = negation();
		$$ = conjonctionBis($1);
	} else {
		erreur("erreur de syntaxe -> symbole ou identifiant attendu.");
	}

	affiche_balise_fermante("conjonction", afficher_synt);
	return $$;
}




n_exp *conjonctionBis(n_exp *herite) {
	n_exp *$2 = NULL;
	n_exp *herite_fils = NULL;
	n_exp *$$ = NULL;

	affiche_balise_ouvrante("conjonctionBis", afficher_synt);

	if (uniteCourante == ET) {
		afficher_element(uniteCourante);
		uniteCourante = yylex();
		$2 = negation();
		herite_fils = conjonctionBis(herite);
		$$ = cree_n_exp_op(et, herite_fils, $2, NULL);
	} else if (est_suivant(uniteCourante, _conjonctionBis_)) {
		$$ = herite;
	} else {
		erreur("erreur de syntaxe -> \'&\' attendu.");
	}

	affiche_balise_fermante("conjonctionBis", afficher_synt);
	return $$;
}




n_exp *negation() {
	n_exp *$$ = NULL;

	affiche_balise_ouvrante("negation", afficher_synt);

	if (uniteCourante == NON) {
		afficher_element(uniteCourante);
		uniteCourante = yylex();
		$$ = comparaison();
	} else if (est_premier(uniteCourante, _comparaison_)) {
		$$ = comparaison();
	} else {
		erreur("erreur de syntaxe -> symbole ou identifiant attendu.");
	}

	affiche_balise_fermante("negation", afficher_synt);
	return $$;
}




n_exp *comparaison() {
	n_exp *$1 = NULL;
	n_exp *$$ = NULL;

	affiche_balise_ouvrante("comparaison", afficher_synt);

	if (est_premier(uniteCourante, _expArith_)) {
		$1 = expArith();
	  	$$ = comparaisonBis($1);
	} else {
		erreur("erreur de syntaxe -> symbole ou identifiant attendu.");
	}

	affiche_balise_fermante("comparaison", afficher_synt);
	return $$;
}




n_exp *comparaisonBis(n_exp *herite) {
	n_exp *$2 = NULL;
	n_exp *herite_fils = NULL;
	n_exp *$$ = NULL;

	affiche_balise_ouvrante("comparaisonBis", afficher_synt);

	if (uniteCourante == EGAL) {
		afficher_element(uniteCourante);
		uniteCourante = yylex();
		$2 = expArith();
		herite_fils = comparaisonBis(herite);
		$$ = cree_n_exp_op(egal, herite_fils, $2, NULL);
	} else if (uniteCourante == INFERIEUR) {
		afficher_element(uniteCourante);
		uniteCourante = yylex();
		$2 = expArith();
		herite_fils = comparaisonBis(herite);
		$$ = cree_n_exp_op(inf, herite_fils, $2, NULL);
	} else if (est_suivant(uniteCourante, _comparaisonBis_)) {
		$$ = herite;
	} else {
		erreur("erreur de syntaxe -> \'=\' ou \'<\' attendu.");
	}

	affiche_balise_fermante("comparaisonBis", afficher_synt);
	return $$;
}




n_exp *expArith() {
	n_exp *$1 = NULL;
	n_exp *$$ = NULL;

	affiche_balise_ouvrante("expArith", afficher_synt);

	if (est_premier(uniteCourante, _terme_)) {
		$1 = terme();
		$$ = expArithBis($1);
	} else {
		erreur("erreur de syntaxe -> symbole ou identifiant attendu.");
	}

	affiche_balise_fermante("expArith", afficher_synt);
	return $$;
}




n_exp *expArithBis(n_exp *herite) {
	n_exp *$2 = NULL;
	n_exp *herite_fils = NULL;
	n_exp *$$ = NULL;

	affiche_balise_ouvrante("expArithBis", afficher_synt);

	if (uniteCourante == PLUS) {
		afficher_element(uniteCourante);
		uniteCourante = yylex();
		$2 = terme();
		herite_fils = expArithBis(herite);
		$$ = cree_n_exp_op(plus, herite_fils, $2, NULL);
	} else if (uniteCourante == MOINS) {
		afficher_element(uniteCourante);
		uniteCourante = yylex();
		$2 = terme();
		herite_fils = expArithBis(herite);
		$$ = cree_n_exp_op(moins, herite_fils, $2, NULL);
	} else if (est_suivant(uniteCourante, _expArithBis_)) {
		$$ = herite;
	} else {
		erreur("erreur de syntaxe -> \'+\' ou \'-\' attendu.");
	}

	affiche_balise_fermante("expArithBis", afficher_synt);
	return $$;
}




n_exp *terme() {
	n_exp *$1 = NULL;
	n_exp *$$ = NULL;

	affiche_balise_ouvrante("terme", afficher_synt);

	if (est_premier(uniteCourante, _facteur_)) {
		$1 = facteur();
		$$ = termeBis($1);
	} else {
		erreur("erreur de syntaxe -> symbole ou identifiant attendu.");
	}

	affiche_balise_fermante("terme", afficher_synt);
	return $$;
}




n_exp *termeBis(n_exp *herite) {
	n_exp *$2 = NULL;
	n_exp *herite_fils = NULL;
	n_exp *$$ = NULL;

	affiche_balise_ouvrante("termeBis", afficher_synt);

	if (uniteCourante == FOIS) {
		afficher_element(uniteCourante);
		uniteCourante = yylex();
		$2 = facteur();
		herite_fils = termeBis(herite);
		$$ = cree_n_exp_op(fois, herite_fils, $2, NULL);
	} else if (uniteCourante == DIVISE) {
		afficher_element(uniteCourante);
		uniteCourante = yylex();
		$2 = facteur();
		herite_fils = termeBis(herite);
		$$ = cree_n_exp_op(divise, herite_fils, $2, NULL);
	} else if (est_suivant(uniteCourante, _termeBis_)) {
		$$ = herite;
	} else {
		erreur("erreur de syntaxe -> \'*\' ou \'/\' attendu.");
	}

	affiche_balise_fermante("termeBis", afficher_synt);
	return $$;
}




n_exp *facteur() {
	n_appel *$1 = NULL;
	n_var *$2 = NULL;
	n_exp *$$ = NULL;
	int entier = 0;

	affiche_balise_ouvrante("facteur", afficher_synt);

	if (uniteCourante == PARENTHESE_OUVRANTE) {
		afficher_element(uniteCourante);
		uniteCourante = yylex();
		$$ = expression();
		if (uniteCourante == PARENTHESE_FERMANTE) {
			afficher_element(uniteCourante);
			uniteCourante = yylex();
		} else {
			erreur("erreur de syntaxe -> \')\' attendue.");
		}
	} else if (uniteCourante == NOMBRE) {
		// Récupération du nombre
		entier = atoi(recuperer_valeur(uniteCourante));
		afficher_element(uniteCourante);
		uniteCourante = yylex();
		$$ = cree_n_exp_entier(entier);
	} else if (est_premier(uniteCourante, _appelFct_)) {
		$1 = appelFct();
		$$ = cree_n_exp_appel($1);
	} else if (est_premier(uniteCourante, _var_)) {
		$2 = var();
		$$ = cree_n_exp_var($2);
	} else if (uniteCourante == LIRE) {
		afficher_element(uniteCourante);
		uniteCourante = yylex();
		if (uniteCourante == PARENTHESE_OUVRANTE) {
			afficher_element(uniteCourante);
			uniteCourante = yylex();
			if (uniteCourante == PARENTHESE_FERMANTE) {
				afficher_element(uniteCourante);
				uniteCourante = yylex();
				$$ = cree_n_exp_lire();
			} else {
				erreur("erreur de syntaxe -> \')\' attendue.");
			}
		} else {
			erreur("erreur de syntaxe -> \'(\' attendue.");
		}
	} else {
		erreur("erreur de syntaxe -> symbole ou identifiant attendu.");
	}

	affiche_balise_fermante("facteur", afficher_synt);
	return $$;
}




n_var *var() {
	n_exp *$2 = NULL;
	n_var *$$ = NULL;
	char *nom;

	affiche_balise_ouvrante("var", afficher_synt);

	if (uniteCourante == ID_VAR) {
		// Récupération du nom de la variable
		nom = recuperer_valeur(uniteCourante);
		afficher_element(uniteCourante);
		uniteCourante = yylex();
		$2 = optIndice();
		if ($2 == NULL) {
			$$ = cree_n_var_simple(nom);
		} else {
			$$ = cree_n_var_indicee(nom, $2);
		}
	} else {
		erreur("erreur de syntaxe -> identifiant de variable attendu.");
	}

	affiche_balise_fermante("var", afficher_synt);
	return $$;
}




n_exp *optIndice() {
	n_exp *$$ = NULL;

	affiche_balise_ouvrante("optIndice", afficher_synt);

	if (uniteCourante == CROCHET_OUVRANT) {
		afficher_element(uniteCourante);
		uniteCourante = yylex();
		$$ = expression();
		if (uniteCourante == CROCHET_FERMANT) {
			afficher_element(uniteCourante);
			uniteCourante = yylex();
		} else {
			erreur("erreur de syntaxe -> \')\' attendue.");
		}
	}	else if (est_suivant(uniteCourante, _optIndice_)) {
		/* RIEN */
	} else {
		erreur("erreur de syntaxe -> \'[\' attendu.");
	}

	affiche_balise_fermante("optIndice", afficher_synt);
	return $$;
}




n_appel *appelFct() {
	n_l_exp *$3 = NULL;
	n_appel *$$ = NULL;
	char *fonction;

	affiche_balise_ouvrante("appelFct", afficher_synt);

	if (uniteCourante == ID_FCT) {
		fonction = recuperer_valeur(uniteCourante);
		afficher_element(uniteCourante);
		uniteCourante = yylex();
		if (uniteCourante == PARENTHESE_OUVRANTE) {
			afficher_element(uniteCourante);
			uniteCourante = yylex();
			$3 = listeExpressions();
			if (uniteCourante == PARENTHESE_FERMANTE) {
				afficher_element(uniteCourante);
				uniteCourante = yylex();
				$$ = cree_n_appel(fonction, $3);
			} else {
				erreur("erreur de syntaxe -> \')\' attendue.");
			}
		} else {
				erreur("erreur de syntaxe -> \'(\' attendue.");
		}
	} else {
		erreur("erreur de syntaxe -> identifiant de fonction attendu.");
	}

	affiche_balise_fermante("appelFct", afficher_synt);
	return $$;
}




n_l_exp *listeExpressions() {
	n_exp *$1 = NULL;
	n_l_exp *$2 = NULL;
	n_l_exp *$$ = NULL;

	affiche_balise_ouvrante("listeExpressions", afficher_synt);

	if (est_premier(uniteCourante, _expression_)) {
		$1 = expression();
		$2 = listeExpressionsBis($$);
		$$ = cree_n_l_exp($1, $2);
	} else if (est_suivant(uniteCourante, _listeExpressions_)) {
		/* RIEN */
	} else {
		erreur("erreur de syntaxe -> symbole ou identifiant attendu.");
	}

	affiche_balise_fermante("listeExpressions", afficher_synt);
	return $$;
}




n_l_exp *listeExpressionsBis(n_l_exp *herite) {
	n_exp *$2 = NULL;
	n_l_exp *herite_fils = NULL;
	n_l_exp *$$ = NULL;

	affiche_balise_ouvrante("listeExpressionsBis", afficher_synt);

	if (uniteCourante == VIRGULE) {
		afficher_element(uniteCourante);
		uniteCourante = yylex();
		$2 = expression();
		herite_fils = listeExpressionsBis(herite);
		$$ = cree_n_l_exp($2, herite_fils);
	} else if (est_suivant(uniteCourante, _listeExpressionsBis_)) {
		$$ = herite;
	} else {
		erreur("erreur de syntaxe -> \',\' attendu.");
	}

	affiche_balise_fermante("listeExpressionsBis", afficher_synt);
	return $$;
}



void analyserSyntaxe(FILE *yyin, int disp_synt, int disp_asynt, int disp_dico, int disp_tab, int disp_mips) {
	initialise_premiers();
	initialise_suivants();
	uniteCourante = yylex();

	do {
		n_prog *p = programme(disp_synt);
		if (disp_asynt) {
			affiche_n_prog(p);
		}

		if (disp_dico) {
			parcours_n_prog(p, disp_tab, disp_mips);
		}

	} while(uniteCourante != FIN);
}
