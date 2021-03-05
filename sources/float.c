#include <stdio.h>
#include <regex.h>

int main(void)
{
    regex_t regex;
    char* regex_string = "^[0-9]+.?[0-9]*$";
    char* string = "148942..";

    int err = regcomp(&regex, regex_string,  REG_EXTENDED);

    if (err == 0) 
    {
        int match = regexec(&regex, string, 0, NULL, 0);

        regfree(&regex);

        if (match == 0) 
        {
            printf("Match");
        }
        else if (match == REG_NOMATCH)
        {
            printf("No Match");
        }
    }
    else 
    {
        printf("Error");
    }
    return 0;
}