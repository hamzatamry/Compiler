#include <stdio.h>
#include "..\headers\regex.h"


int main()
{
    char* number_pattern = "^[+-]?([0-9]*[.])?[0-9]+$";
    char* string_pattern =  "^(\"|\').*(\"|\')$";
    char* character_pattern = "^\'.\'$";
    char* identifier_pattern =  "^[a-z_][a-z_A-Z1-9]*$";
    char* iterable_pattern = "^[a-z_][a-z_A-Z1-9]*(\\[\\])+$";

    printf("%d", match("array[]", iterable_pattern));

    return 0;
}