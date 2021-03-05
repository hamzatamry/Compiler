#include <stdio.h>
#include "..\headers\regex.h"


int main()
{
    /*
    
    {,,,}
    [,,,]
    (,,,)
    {
        zegze: zgzeg,
        zegzeg: zegzeg,
    }
    */


    char* number_pattern = "^[+-]?([0-9]*[.])?[0-9]+$";
    char* string_pattern =  "^(\"|\').*(\"|\')$";
    char* character_pattern = "^\'.\'$";
    char* identifier_pattern =  "^[a-z_][a-z_A-Z1-9]*$";
    char* iterable_pattern = "^[a-z_][a-z_A-Z1-9]*(\\[\\])+$";
    char* iterable_value_pattern = "";
    char* structure_pattern = "";
    char* dictionnary_pattern = "";

    printf("%d", match("array[]", iterable_pattern));

    return 0;
}