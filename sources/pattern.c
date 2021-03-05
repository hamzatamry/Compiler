#include <stdio.h>
#include "..\headers\regex.h"

/*
    {,,,}
    [,,,]
    (,,,)
    {
        zegze: zgzeg,
        zegzeg: zegzeg,
    }
*/


int main(void)
{
    char* identifier_pattern =  "^[a-z_][a-z_A-Z1-9]*$";
    char* number_pattern = "^[+-]?([0-9]*[.])?[0-9]+$";
    char* string_pattern =  "^(\"|\').*(\"|\')$";
    char* character_pattern = "^\'.\'$";
    char* array_declaration_pattern = "^[a-z_][a-z_A-Z1-9]*(\\[\\])+$";

    printf("%d", match("array[]", array_declaration_pattern));

    return 0;
}