*   Before transformation to LL(1)
```
DOWHILELOOP_STATEMENT       ->  do accolade_ouverte STATEMENTS accolade_fermante while (CONDITION) ;
                            |   repeat STATEMENTS until CONDITION; 
                            |   .
```
*   After transformation to LL(1)
```

```
*   remarks (to be compatible with the tool)
```
accolade_ouverte    { 
accolade_fermante   }
```