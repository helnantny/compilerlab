%{
#include <stdio.h>
int vowels = 0;
int consonants = 0;
%}

%%
[aeiouAEIOU]          { vowels++; }      
[a-zA-Z]              { consonants++; }   
.|\n                  { ; }               
%%

int yywrap()
{
    return 1;
}

int main()
{
    printf("Enter a string:\n");
    yylex();
    
    // Display the final counts
    printf("\n");
    printf("Number of  Vowels     : %d\n", vowels);
    printf("Number of  Consonants : %d\n", consonants);
    
    return 0;
}
