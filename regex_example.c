#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

int main (void)
{
   int err;
   regex_t preg;
   const char* str_request = "www.developpez.com";
   const char* str_regex = "www\\.[-_[:alnum:]]+\\.[[:lower:]]{2,4}"; //regex

   err = regcomp(&preg, str_regex, REG_NOSUB | REG_EXTENDED); //compile the regex

   if (err == 0)
   {
      int match;

      match = regexec(&preg, str_request, 0, NULL, 0);

      regfree(&preg);

      if (match == 0)
      {
         printf("%s est une adresse internet valide\n", str_request);
      }
      else if (match == REG_NOMATCH)
      {
         printf("%s n\'est pas une adresse internet valide\n", str_request);
      }
   }
   return (EXIT_SUCCESS);
}