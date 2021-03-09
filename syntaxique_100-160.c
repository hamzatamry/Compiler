


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
            ERREUR(TYPE_ERR);
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
		INSTRUCTIONS();
		Test_Symbole(ACF_TOKEN,ACF_ERR);
	}
	else {
		INSTRUCTION();
	}
}
void Fid3(){
	if(SYM_COUR.CODE == IN_TOKEN){
		Test_Symbole(ID_TOKEN,ID_ERR);
		Test_Symbole(ACO_TOKEN,ACO_ERR);
		INSTRUCTIONS();
		Test_Symbole(ACF_TOKEN,ACF_ERR);
	}
	else{
		Test_Symbole(EQU_TOKEN,EQU_ERR);
		Test_Symbole(NUM_TOKEN,NUM_ERR);
		Test_Symbole(TO_TOKEN,TO_ERR);
		Test_Symbole(NUM_TOKEN,NUM_ERR);
		Test_Symbole(DO_TOKEN,DO_ERR);
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
	FCONDITIONS2();
}

void FCONDITIONS2(){
	if(SYM_COUR.CODE == ACO_TOKEN){
		INSTRUCTIONS();
		Test_Symbole(ACF_TOKEN,ACF_ERR)
	}
	else{
		INSTRUCTION();
	}
}

void DOWHILELOOP_STATEMENT(){
	if(SYM_COUR.CODE == DO_TOKEN){
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
	if(NOT_TOKEN == SYM_COUR.CODE){
		Test_Symbole(PO_TOKEN,PO_ERR);
		CONDITION();
		Test_Symbole(PF_TOKEN,PF_ERR);
	}
	else if(SYM_COUR.CODE == NOT1_TOKEN){
		Test_Symbole(PO_TOKEN,PO_ERR);
		CONDITION();
		Test_Symbole(PF_TOKEN,PF_ERR);
	}
	else{
		CONDITION();
		FCONDITION();
	}
}


void FCONDITION(){
	if(SYM_COUR.CODE == AND_TOKEN || SYM_COUR.CODE == OR_TOKEN || SYM_COUR.CODE == AND1_TOKEN || SYM_COUR.CODE == OR1_TOKEN)
		CONDITIONS();
}

void CONDITION(){
	EXPRESSION();
	COMPARATOR();   // TO IMPLEMENT LATER
	EXPRESSION();
}

void INPUT_OUTPUT(){
	if(SYM_COUR.CODE == PRINT_TOKEN || SYM_COUR.CODE == PRINTF_TOKEN || SYM_COUR.CODE == SCANF_TOKEN || SYM_COUR.CODE == INPUT_TOKEN ||
		SYM_COUR.CODE == LOG_TOKEN || SYM_COUR.CODE == FPRINTF_TOKEN || SYM_COUR.CODE == FSCANF_TOKEN || SYM_COUR.CODE == FREADF_TOKEN || SYM_COUR.CODE == FREADF_TOKEN
		|| SYM_COUR.CODE == FWRITEF_TOKEN || SYM_COUR.CODE == WRITE_TOKEN || SYM_COUR.CODE == READ_TOKEN || SYM_COUR.CODE == PUTS_TOKEN || SYM_COUR.CODE == GETS_TOKEN){
			Test_Symbole(PO_TOKEN,PO_ERR);
			ARGUMENT();
			Test_Symbole(PF_TOKEN,PF_TOKEN);

	}
}


void FONCTION(){
	if(SYM_COUR.CODE == DEF_TOKEN){
		Test_Symbole(TYPE_TOKEN, TYPE_ERR);
		FONCTION2();
	}
	else{
		Test_Symbole(FUNCTION_TOKEN, FUNTION_ERR);
		Test_Symbole(TYPE_TOKEN,TYPE_ERR);
		FONCTION2();
	}
}
