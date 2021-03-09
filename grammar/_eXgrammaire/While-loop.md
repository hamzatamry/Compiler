*   Before transformation to LL(1)
```
WHILELOOP_STATEMENT     ->  while ( CONDITION ) STATEMENT
                        |   while ( CONDITION ) accolade_ouvrante STATEMENTS accolade_fermante
                        |   while CONDITION : entree tab STATEMENTS
                        |   while ( CONDITION ) do STATEMENTS ;
                        |   .
```
*   After transformation to LL(1)
```

```
*   remarks (to be compatible with the tool)
```
accolade_ouverte    { 
accolade_fermante   }
entree              \n 
tab                 \t
```