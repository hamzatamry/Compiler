*   Before transformation to LL(1)
```
FORLOOP_STATEMENT       ->  for (VAR_DECLARATION ; CONDITION ; INSTRUCTION) accolade_ouverte STATEMENTS accolade_fermante
                        |   for (VAR_DECLARATION ; CONDITION ; INSTRUCTION) STATEMENT 
                        |   for (VAR_DECLARATION : ITERABLE) accolade_ouverte STATEMENTS accolade_fermante   
                        |   for (VAR_DECLARATION : ITERABLE) STATEMENT 
                        |   for ITERATOR in ITERABLE : entree tab STATEMENTS
                        |   for VAR_ID affectation NOMBRE to NOMBRE do STATEMENTS ; 
                        |   .
```
*   After transformation to LL(1)
```
FORLOOP_STATEMENT →	for Ffor
|	.
Ffor →	(VAR_DECLARATION F(VAR_DECLARATION
|	ITERATOR in ITERABLE : entree tab STATEMENTS
|	VAR_ID affectation NOMBRE to NOMBRE do STATEMENTS ; .
F(VAR_DECLARATION →	; F;
|	: F: .
F; →	CONDITION FCONDITION .
FCONDITION →	; F;1 .
F;1 →	INSTRUCTION) FINSTRUCTION) .
FINSTRUCTION) →	accolade_ouverte STATEMENTS accolade_fermante
|	STATEMENT .
F: →	ITERABLE) FITERABLE) .
FITERABLE) →	accolade_ouverte STATEMENTS accolade_fermante
|	STATEMENT .
```
*   remarks (to be compatible with the tool)
```
accolade_ouverte    { 
accolade_fermante   }
egal                =
entree              \n 
tab                 \t
affectation         :=
```