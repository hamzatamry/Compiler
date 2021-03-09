#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include "..\headers\lexical.h"
#include "..\headers\regex.h"

FILE* flux_input;
FILE* flux_output;
char Car_Cour;
TSym_Cour SYM_COUR;

Error MESSAGE_ERR[100] = {
    { NUM_ERR     , "Valeur numero incorrecte" },
    { CHAR_ERR, "Valeur caractere incorrecte" },
    { FICH_VID_ERR, "fichier vide" },
    { ID_LONG_ERR, "identificateur long" },
    { ID_INC_ERR, "identificateur incorrect" },
    { COMMENT_ERR, "erreur commentaire" },
    { STRING_ERR, "string non proprement declare : missing \"" }
};

const char tokens[][20] = {  
    "int", "integer", "number", "float", "char", "string", "str", "long", "double",                                   
    "short", "unsigned", "boolean", "bool", "let", "$", "byte", "auto", "void", "true", "false",                      
    "program", "const", "var", "begin", "end", "if", "then", "while", "do", "read", "write", "switch", "goto", "def", "function" ,                               
    ";", ".", ":", "+", "add", "-", "minus", "*", "mult", "/", "div", "per", "%%", "mod",                    
    "modulo", ",", "=", ":=", "affect", "<-", "<", "lss", "<=", "leq", ">", "gtr", ">=", "geq", "==" , "equ",      
    "is", "===", "in", "**", "**=", "+=", "-=", "*=", "/=", "%%=", "^=", "&=", "|=", "++", "--",                      
    "<>", "(",")", "/*" , "*/", "{", "}", "^", "~", "<<", ">>", "&", "|", "&&", "and", "||", "or", "!", "not", "\"", "\'", "EOF",
    "ID", "NUM", "ELSE", "UNTIL", "REPEAT", "for", "DOWNTO", "CASE", "OF", "INTO", "return", "print", "printf", "scanf", "input",
    "log", "fprintf", "fscanf", "fread", "fwrite", "puts", "gets", "call","STRINGVAL", "LE RESTE", "CHAR_VALUE_TOKEN"                                 
};

const char lexical_unit[][20] = {
    "INT_TOKEN", "INTEGER_TOKEN", "NUMBER_TOKEN", "FLOAT_TOKEN", "CHAR_TOKEN", "STRING_TOKEN", "STR_TOKEN", "LONG_TOKEN",
    "DOUBLE_TOKEN", "SHORT_TOKEN", "UNSIGNED_TOKEN", "BOOLEAN_TOKEN", "BOOL_TOKEN", "LET_TOKEN", "$_TOKEN", "BYTE_TOKEN", "AUTO_TOKEN", 
    "VOID_TOKEN", "TRUE_TOKEN", "FALSE_TOKEN", "PROGRAM_TOKEN", "CONST_TOKEN", "VAR_TOKEN", "BEGIN_TOKEN", "END_TOKEN", "IF_TOKEN", "THEN_TOKEN",
    "WHILE_TOKEN", "DO_TOKEN", "READ_TOKEN", "WRITE_TOKEN", "SWITCH_TOKEN", "GOTO_TOKEN", "DEF_TOKEN", "FUNCTION_TOKEN", "PV_TOKEN", "PT_TOKEN", 
    "PTS_TOKEN", "PLUS_TOKEN", "ADD_TOKEN", "MOINS_TOKEN", "MINUS_TOKEN","MULT_TOKEN","MULT1_TOKEN", "DIV_TOKEN","DIV1_TOKEN", "PER_TOKEN", "MOD_TOKEN",
    "MOD1_TOKEN", "MODULO_TOKEN", "VIR_TOKEN", "EG_TOKEN", "AFFECPASCAL_TOKEN", "AFFECT_TOKEN"," AFFECARROW_TOKEN", "INF_TOKEN", "LSS_TOKEN", 
    "INFEG_TOKEN", "LEQ_TOKEN", "SUP_TOKEN", "GTR_TOKEN", "SUPEG_TOKEN","GEQ_TOKEN", "EQU_TOKEN", "EQU1_TOKEN", "IS_TOKEN", "TRIPPLEEQU_TOKEN",
    "IN_TOKEN", "PUISS_TOKEN", "PUISSAFFEC_TOKEN", "ADDAFFEC_TOKEN", "MINUSAFFEC_TOKEN", "MULTAFFEC_TOKEN", "DIVAFFEC_TOKEN", "MODAFFEC_TOKEN",
    "BXORAFFEC_TOKEN", "BANDAFFEC_TOKEN", "BORAFFEC_TOKEN","INCREM_TOKEN", "DECREM_TOKEN","DIFF_TOKEN", "PO_TOKEN", "PF_TOKEN", "DC_TOKEN", "FC_TOKEN",
    "ACO_TOKEN", "ACF_TOKEN", "BXOR_TOKEN", "TILD_TOKEN", "LEFTSHIFT_TOKEN", "RIGHTSHIFT_TOKEN", "BAND_TOKEN", "BOR_TOKEN", "AND_TOKEN", "AND1_TOKEN", 
    "OR_TOKEN", "OR1_TOKEN", "NOT_TOKEN", "NOT1_TOKEN", "QUOTE_TOKEN", "SINGLEQUOTE_TOKEN", "EOF_TOKEN", "ID_TOKEN", "NUM_TOKEN", "ELSE_TOKEN", "UNTIL_TOKEN", "REPEAT_TOKEN", "FOR_TOKEN",
    "DOWNTO_TOKEN", "CASE_TOKEN", "OF_TOKEN", "INTO_TOKEN" , "RETURN_TOKEN","PRINT_TOKEN", "PRINTF_TOKEN", "SCANF_TOKEN", "INPUT_TOKEN", "LOG_TOKEN", "FPRINTF_TOKEN", "FSCANF_TOKEN", "FREAD_TOKEN", "FWRITE_TOKEN", 
    "PUTS_TOKEN", "GETS_TOKEN","CALL_TOKEN", "STRINGVAL_TOKEN", "ERREUR_TOKEN", "CHAR_VALUE_TOKEN"
};

void ouvrir_fichier(char nom[20])
{
    flux_input = fopen(nom, "r");

    flux_output = fopen("tests\\output\\out_1", "w");

    if (flux_input == NULL || flux_output == NULL)
    {
        printf("erreur d'ouverture du fichier");
    } 
    else
    {
        lire_car();
        if (Car_Cour == EOF)
        {
            ERREUR(FICH_VID_ERR);
        }
    }
    
}

void lire_car()
{
    Car_Cour = fgetc(flux_input);
}

_Bool isSeparator()
{
    return (Car_Cour == ' ') || (Car_Cour == '\n') || (Car_Cour == '\t');
}

int mot_cle()
{
    for (int i = 0; i < 127; i++)
    {
        if (strcmp(tokens[i], SYM_COUR.NOM) == 0)
            return i;
    }
    return -1;
}

void isID()
{
    int n = strlen(SYM_COUR.NOM);
    SYM_COUR.CODE = ID_TOKEN;
    if (n > 20)
    {
        SYM_COUR.CODE = ERREUR_TOKEN;
        ERREUR(ID_LONG_ERR);
    }
    else
    {
        for (int i = 0; i < n; i++)
        {
            char c = SYM_COUR.NOM[i];
            if (i == 0 && !isalpha(c))
            {
                SYM_COUR.CODE = ERREUR_TOKEN;
                ERREUR(ID_INC_ERR);
            
            }

            if (!isalpha(c) && !isdigit(c))
            {
                SYM_COUR.CODE = ERREUR_TOKEN; 
                ERREUR(ID_INC_ERR);
            }
        }
        
    }
    
}

void isString()
{
    int i = 0;
    do
    {
        SYM_COUR.NOM[i] = Car_Cour;
        i++;
        lire_car();
    }while (Car_Cour != '"' && Car_Cour != EOF);
    
    if (Car_Cour == '"')
    {
        SYM_COUR.NOM[i] = Car_Cour;
        i++;
        SYM_COUR.CODE = STRINGVAL_TOKEN;
    }
    else
    {
        SYM_COUR.CODE = ERREUR_TOKEN;
        ERREUR(STRING_ERR);
    }

     SYM_COUR.NOM[i] = '\0';
     lire_car();

}

void isChar()
{
    int i = 0;

    do 
    {
        SYM_COUR.NOM[i] = Car_Cour;
        lire_car();
        i++;
    }
    while (Car_Cour != EOF && Car_Cour != '\'');

    SYM_COUR.NOM[i] = '\'';
    SYM_COUR.NOM[i + 1] = '\0';

    if (Car_Cour == EOF)
    {
        SYM_COUR.CODE = ERREUR_TOKEN;
        ERREUR(CHAR_ERR);
        return;
    }

    if (match(SYM_COUR.NOM, "^\'.\'$"))
    {
        SYM_COUR.CODE = CHAR_VALUE_TOKEN; 
    }
    else 
    {
        SYM_COUR.CODE = ERREUR_TOKEN;
        ERREUR(CHAR_ERR);

    }

    lire_car();
}

_Bool isSpecial()
{
    switch (Car_Cour)
    {
    case ';':
        break;
    case '.':
        break;
    case '+':
        break;
    case '-':
        break;
    case '*':
        break;
    case '/':
        break;
    case ',':
        break;
    case '(':
        break;
    case ')':
        break;
    case '<':
        break;
    case '>':
        break;
    case '=':
        break;
    case ':':
        break;
    case '{':
        break;
    case '}':
        break;
    case '^':
        break;
    case '$':
        break;
    case '&':
        break;
    case '~': 
        break;
    case '|':
        break;
    case '!':
        break;
    case '?':
        break;
    // case '\"':
    //     break;
    default:
    return false;
    }
    return true;
}

void lire_mots()
{
    int i = 0;
    while (!isSeparator() && !isSpecial() && Car_Cour != '\'' && Car_Cour != '"')
    {
        SYM_COUR.NOM[i] = Car_Cour;
        lire_car();
        i++;
    }
    SYM_COUR.NOM[i] = '\0';

    if (mot_cle() != -1)
    {
        SYM_COUR.CODE = mot_cle();
    }  
    else
    {
        isID();
    }
}

void lire_nombres()
{
    int i = 0;

    while (isdigit(Car_Cour) || Car_Cour == '.')
    {
        SYM_COUR.NOM[i] = Car_Cour;
        lire_car();
        i++;
    }

    SYM_COUR.NOM[i] = '\0';

    if (match(SYM_COUR.NOM, "^([0-9]*[.])?[0-9]+$"))
    {
        SYM_COUR.CODE = NUM_TOKEN; 
    }
    else 
    {
        ERREUR(NUM_ERR);
    }
}

void lire_specials()
{
    bool string = false;

    switch (Car_Cour)
    {
    case ';':
        SYM_COUR.CODE = PV_TOKEN;
        lire_car();
        break;
    case '.':
        SYM_COUR.CODE = PT_TOKEN;
        lire_car();
        break;
    case '+':
        SYM_COUR.CODE = PLUS_TOKEN;
        lire_car();
        if (Car_Cour == '=') {
            SYM_COUR.CODE = ADDAFFEC_TOKEN;
            lire_car();
        }
        if (Car_Cour == '+'){
            SYM_COUR.CODE = INCREM_TOKEN;
            lire_car();
        }
        break;
    case '-':
        SYM_COUR.CODE = MOINS_TOKEN;
        lire_car();
        if (Car_Cour == '=') {   
            SYM_COUR.CODE = MINUSAFFEC_TOKEN;
            lire_car();
        }
        if (Car_Cour == '-') {
            SYM_COUR.CODE = DECREM_TOKEN;
            lire_car();
            }
        break;
    case '*':
        SYM_COUR.CODE = MULT_TOKEN;
        lire_car();
        if (Car_Cour == '='){
            SYM_COUR.CODE = MULTAFFEC_TOKEN;
            lire_car();
        }
        if (Car_Cour == '*')
        {
            SYM_COUR.CODE = PUISS_TOKEN;
            lire_car();
            if (Car_Cour == '=') {
                SYM_COUR.CODE = PUISSAFFEC_TOKEN;
                lire_car();
            }
        }
        break;
    case '/':
        SYM_COUR.CODE = DIV_TOKEN;
        lire_car();
        if (Car_Cour == '='){
            SYM_COUR.CODE = DIVAFFEC_TOKEN;
            lire_car();
        }
        if (Car_Cour == '*')
        {
            strcpy(SYM_COUR.NOM,"/*");
            SYM_COUR.CODE = DC_TOKEN;
            afficher_token();
            lire_car();
            while (Car_Cour != '*' && Car_Cour != EOF)
                lire_car();
            if (Car_Cour == '*')
            {
                lire_car();
                if (Car_Cour == '/')
                {
                    strcpy(SYM_COUR.NOM,"*/");
                    SYM_COUR.CODE = FC_TOKEN; // check here
                    lire_car(); 
                }   
            }
            else
            {
                SYM_COUR.CODE = ERREUR_TOKEN;
                ERREUR(COMMENT_ERR);
            }
               
        }
        break;
    case ',':
        SYM_COUR.CODE = VIR_TOKEN;
        lire_car();
        break;
    case '(':
        SYM_COUR.CODE = PO_TOKEN;
        lire_car();
        break;
    case ')':
        SYM_COUR.CODE = PF_TOKEN;
        lire_car();
        break;
    case '<':
        SYM_COUR.CODE = INF_TOKEN;
        lire_car();
        if (Car_Cour == '=')
           { 
            SYM_COUR.CODE = INFEG_TOKEN;
            lire_car();
           }
        if (Car_Cour == '>')
           { 
            SYM_COUR.CODE = DIFF_TOKEN;
            lire_car();
            }
        if (Car_Cour == '<') {    
            SYM_COUR.CODE = LEFTSHIFT_TOKEN;
            lire_car();
         }
        if (Car_Cour == '-') {
            SYM_COUR.CODE = AFFECARROW_TOKEN;
            lire_car();
        }
            
        break;

    case '>':
        SYM_COUR.CODE = SUP_TOKEN;
        lire_car();
        if (Car_Cour == '=') {
            SYM_COUR.CODE = SUPEG_TOKEN;
            lire_car();
        }
        if (Car_Cour == '>') {
            SYM_COUR.CODE == RIGHTSHIFT_TOKEN;
            lire_car();
        }
        break;
    case '=':
        SYM_COUR.CODE = EG_TOKEN;
        lire_car();
        if (Car_Cour == '='){
            SYM_COUR.CODE = EQU_TOKEN;
            lire_car();
        }
        break;
    case ':':
        SYM_COUR.CODE = PTS_TOKEN;
        lire_car();
        if (Car_Cour == '=') {
            SYM_COUR.CODE = AFFECPASCAL_TOKEN;
            lire_car();
        }
        break;
    case '{':
        SYM_COUR.CODE = ACO_TOKEN;         // check here 
        lire_car();
        if (Car_Cour == '*')
        {
            strcpy(SYM_COUR.NOM,"{*");
            SYM_COUR.CODE = DC_TOKEN;
            afficher_token();
            lire_car();
            while (Car_Cour != '*' && Car_Cour != EOF)
                lire_car();
            if (Car_Cour == '*')
            {
                lire_car();
                if (Car_Cour == '}')
                {
                    strcpy(SYM_COUR.NOM,"*}");
                    SYM_COUR.CODE = FC_TOKEN; // check here
                    lire_car(); 
                }   
            }
            else
            {
                SYM_COUR.CODE = ERREUR_TOKEN;
                ERREUR(COMMENT_ERR);
            }
               
        }
        break;
    case '}':
        SYM_COUR.CODE = ACF_TOKEN;
        lire_car();
        break;
    case '^':
        SYM_COUR.CODE = BXOR_TOKEN;
        lire_car();
        if (Car_Cour == '=') {
            SYM_COUR.CODE = BXORAFFEC_TOKEN;
            lire_car();
        }
        break;
    case '$':
         SYM_COUR.CODE = $_TOKEN;
         lire_car();
        break;
    case '&':
        SYM_COUR.CODE = BAND_TOKEN;
        lire_car();
        if (Car_Cour == '='){
            SYM_COUR.CODE = BANDAFFEC_TOKEN;
            lire_car();
        }
        if (Car_Cour == '&'){
            SYM_COUR.CODE = AND_TOKEN;
            lire_car();
        }
        break;
    case '~': 
         SYM_COUR.CODE = TILD_TOKEN;
         lire_car();
        break;
    case '|':
        SYM_COUR.CODE = BOR_TOKEN;
        lire_car();
        if (Car_Cour == '=') {
            SYM_COUR.CODE = BORAFFEC_TOKEN;
            lire_car();
        }
        if (Car_Cour == '|') {
            SYM_COUR.CODE = OR_TOKEN;
            lire_car();
        }
        break;
    case '!':
        SYM_COUR.CODE = NOT_TOKEN;
        lire_car();
        break;
    case '?':                             // à ajouter
        break;
    // case '\"':
    //     isString();
    //     lire_car();
    //     string = true;
    //     break;
    default:
        SYM_COUR.CODE = ERREUR_TOKEN;
    }
    // if(!string)
    // {
        strcpy(SYM_COUR.NOM, tokens[SYM_COUR.CODE]);
        //lire_car();
    // }
  
    
}

void sym_suiv()
{
    while (isSeparator())
    {
        lire_car();
    }

    if (isSpecial())
    {
        lire_specials();
    }
    else if (isdigit(Car_Cour))
    {
        lire_nombres();
    }
    else if (Car_Cour == '"')
    {
        isString();
    }
    else if (Car_Cour == '\'')
    {
        isChar();
    }
    else
    {
        lire_mots();
    }
}

void afficher_token()
{
    printf("%s -> %s\n", SYM_COUR.NOM, lexical_unit[SYM_COUR.CODE]);
    fprintf(flux_output, "%s %d\n", SYM_COUR.NOM, SYM_COUR.CODE);
    fflush(flux_output);
}

void ERREUR(ERREURS e)
{
    printf("%s -> %s\n", SYM_COUR.NOM, MESSAGE_ERR[e].msg);
}

/****************************************************************************************************************************/
