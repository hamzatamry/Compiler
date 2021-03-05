#include <stdio.h>
#include "..\headers\regex.h"


int main()
{
    char* number_pattern = "^[+-]?([0-9]*[.])?[0-9]+$";
    char* string_pattern =  "^(\"|\').*(\"|\')$";
    char* character_pattern = "^\'.\'$";

    printf("%d", match("\'$\'", character_pattern));

    return 0;
}