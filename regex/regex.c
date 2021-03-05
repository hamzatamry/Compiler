#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

int match(char* string, char* pattern)
{
    regex_t regex;

    int err = regcomp(&regex, pattern,  REG_EXTENDED);

    if (err == 0) 
    {
        //0 succès
        //1 échéc
        
        int match = regexec(&regex, string, 0, NULL, 0);

        regfree(&regex);

        return (match == 0);

        //REG_NOMATCH
    }
    else 
    {
        return -1; //regex compilation failed
    }
}