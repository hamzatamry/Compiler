*   Before transformation to LL(1)
```
FORLOOP_STATEMENT       ->  for (VAR_DECLARATION ; CONDITION ; STEP) accolade_ouverte STATEMENTS accolade_fermante
                        |   for (VAR_DECLARATION ; CONDITION ; STEP) STATEMENT 
                        |   for (VAR_DECLARATION : CONDITION) accolade_ouverte STATEMENTS accolade_fermante   
                        |   for (VAR_DECLARATION : CONDITION) STATEMENT 
                        |   for ITERATOR in ITERABLE : entree tab STATEMENTS
                        |   for VAR_ID : egal NOMBRE to NOMBRE do STATEMENTS ; 
                        |   .
```
*   After transformation to LL(1)
```

```
*   remarks (to be compatible with the tool)
```
accolade_ouverte    { 
accolade_fermante   }
egal                =
entree              \n 
tab                 \t
```