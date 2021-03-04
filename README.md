# Projet_Compilation
    
*   Nom du langage : Universal (one_for_all)
*   Liste des langages inclus : python, javascript, c, c++, java, typescript, shell script, batch script, Pascal

## Regular expressions docs

*    [docs](https://www.geeksforgeeks.org/regular-expressions-in-c/)

## Affectation des roles
    
*   hamza + zakaria = VAR_DECLARATION, BOUCLE, EXCEPTION
*   abdelwadoud + rida = CONTROLE, BLOCK_PASCAL
*   yasser + said = AFFECTATION, FONCTION, APPEL_FONCTION

## GrammaireLL(1)

*   G = <T={:, =, const, ;, end}, NT={S, INSTS}, S, P={r1, ...}>

*   BLOCK
```
r: S               ->  S'$
r: S'              ->  INSTS
r:                  |  BLOCK 
r:                  |  eps
r: INSTS           ->  INST; INSTS
r:                  |  eps
r: INST            ->  VAR_DECLARATION
r:                  |  BOUCLE
r:                  |  CONTROLE
r:                  |  APPEL_FONCTION
r:                  |  AFFECTATION
r:                  |  FONCTION
r:                  |  EXCEPTION
r: BLOCK           ->  BLOCK_PASCAL          
```
*   VAR_DECLARATION
```
VAR_DECLARATION -> VARS' VAR_DECLARATIONS
                        | eps
VARS'          -> const TYPE CONST' {, CONST'}      
                        | let ID : TYPE OPT {, ID : TYPE OPT}      
                        | ID : TYPE OPT {, ID : TYPE OPT}    
                        | ID is TYPE OPT {, ID is TYPE OPT} 
CONST'         -> AFFECTATION      // make sure this case will be added in AFFECTATION rule(AFFECTAION_ID) 
                        | ID 
OPT           ->  eps
                        | AFFECTATION      // make sure this case will be added in AFFECTATION rule(AFFECTAION_TYPE)
TYPE          -> String | Number | int | boolean | bool | char   
```
*   BOUCLE
```

```
*   EXCEPTION
```

```
*   CONTROLE
```
if_stmt
	: IF ['(' expression ')' block [elif_stmt | else_block | e]  |  expresssion ':' block]
	| SWITCH '(' expression ')' block
	end


elif_stmt:
    | 'elif' expression ':' block [elif_stmt | else_block] 

else_block: 'else' [':' | e] block 

shorthand: expression '?' statement ':' statement

block: statement
	|
end
	: ';'
	| e
```
*   BLOCK_PASCAL
```

```
*   AFFECTATION
```
AFFECTATION' ->  ID :=  EXPRESSION ;
              |  ID :   EXPRESSION ;
              |  ID =   EXPRESSION ;
              |  ID <-  EXPRESSION ;

AFFECTATION  ->  const AFFECTATION'
              |  AFFECTATION'

EXPRESSION   ->   TERM 
              | TERM OPERATEURADD TERM

TERM        ->    FACTEUR OPERATEURMULT FACTEUR
              | FACTEUR
              | FACTEUR OPERATEURSPECIAUX


FACTEUR      -> ID 
              | NUMBER 
              | ( EXPRESSION )

OPERATEURSPECIAUX ->  ++
                    | -- 
                    
OPERATEURADD      ->   + 
                    |  -

OPERATEURMULT    ->   *
                    |  \
                    |  % 
                    |  mod
                    |  modulo 
```
*   FONCTION
```
FONCTION     ->  TYPE  FONCTION'
              |   function FONCTION'
FONCTION'    -> ID(PARAMETERS){ INSTS };

PARAMETERS    -> eps
              | PARAMETER 

PARAMETER     ->ID TYPE 
              | PARAMETER , ID TYPE
```
*   APPEL_FONCTION
```
APPEL_FONCTIOn -> ID ( PARAMETERS ) ;
```
* AUTRES
```

```

## les opérateurs

-   opérateur affectation
    
    ```
        = affect <- := 
    ```
   
-   opérateurs arithmétiques

    ```
        + add  
        - minus 
        * mult
        / div per
        % mod modulo
    ```
        
-   opérateurs de traitement de bits

    ```
        ^  
        ~ 
        << 
        >> 
        & 
        |
    ```

-   opérateurs logiques

    ```
        && and 
        || or 
        ! not 
    ```

-   opérateurs de comparaison

    ```
        < lss
        > gtr
        <= leq
        => GEQ
        == equ is
        ===
        in 
    ```
        
-   Autres opérateurs

    ```
        **
        += 
        -=
        *=
        /= 
        %= 
        ^= 
        &=
        |=
        **= 
        ++ 
        --
        ,
    ```

## les types

    int (c, c++, java), Integer(java, c#), number(typescript, PLSQL)
    float (c, c++, java), 
    string, String, str

    float, long, double, short int, long int, long long, long double, unsigned, boolean, bool, Boolean, 
    var, let, $, string, String, Byte, auto, char

## Declaration des variables

    [const] <variable_type> <variable_name> [:][= <value>]; (C, C++, Java, C#) 
    let <variable_name> : <variable_type> [:][= <value>]; (typescript, javascript)
    const <variable_name> : <variable_type> [:][= <value>]; (typescript, javascript)
    <variable_name> : <variable_type> [:][= <value>]; (python)
    <var_name> is <var_type> [:][= <value>]; (dyalna)

## les structures conditionnelles du langage
    
    if (<condition>) 
    {

    } 
    else if (<condition>)
    {

    } 
    else 
    {

    }
    
    <condition> ? <if_true> : <if_false> 
    
    if <condition>:
        ___
    elif <condition>:
        ___
    else:
        ___


## les boucles à prendre en considération

    for (<initial>; <condition>; <step>) 
    {
        [break;]
    }

    while (<condition>)
    {
        [
            break; 
            continue;
        ]
    }

    do 
    {
    } while (<condition>);

    for <iterator> in <iterable>:
        ____

    for (<interator> : <iterable>)
    {

    }

    :loop
        if <condition> do
            exit;
        done
    goto :loop;

    switch ()
    {
        case __: ____; break;

        default: ___;
    }
    

## les instruction de saisi/affichage de base (comme printf, scanf en langage C)

    printf()
    scanf()
    print()
    input()
    log()
    fprintf()
    fscanf()
    fread()
    fwrite()
    write()
    read()
    puts()
    gets()
    cout << ___;
    cin >> ____;
    fopen("", "")
    open("", "")
    fclose()
    close()
    echo


## Autre, comme:  ( , [ , {...

    <return_type> <function_name>([<variable_declaration>, ...]) 
    {
        return
    }

    def <function_name>(...):
        ______
        return 

    let do
    _____

    function <function_name>(....) 
    {

    }

    try
        ___
    except <exception_object> [as <name>]:
        ___
    else:
        ___

    try 
    {

    }
    catch()
    {

    }
    finally()
    {

    }

    <function_name>([parameters, ...]);

## Tout autre élément qui vous semble nécessaire

