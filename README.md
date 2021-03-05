# Analyseur lexical 

## Compilation command
```
gcc main.c sources\*.c -o lexical
```
## Documentation

*   [docs](https://www.geeksforgeeks.org/flex-fast-lexical-analyzer-generator/)

## Download Links

*   [Flex](https://sourceforge.net/projects/gnuwin32/)

## Instructions 

*   1.  Create a file with .l extension
*   2.  Write Lex code inside that file
*   3.  Compile file using the following command 
``` command
    flex <file_name>
```
*   4.  lex.yy.c c-source file will be generated after compilation
*   5.  Compile lex.yy.c and you're done  

## Regex installation and execution

1.  Download [Regex](https://www.mediafire.com/file/m5tm1u8q9xmows9/regex.rar/file)
2.  Extract bin to compiler's bin, lib to compiler's lib and include to compiler's include 
3.  To run a program that includes regex library add -lregex to the compilation command as follow
```
gcc program.c -o output -lregex
```
## Regex code Example
```
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

      match = regexec(&preg, str_request, 0, NULL, 0); //compare the string to the regular expression

      regfree(&preg);   //free the regular expression

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
```
