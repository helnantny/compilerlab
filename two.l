%{
#include <stdio.h>
int lines = 0;
int words = 0;
int chars = 0;
%}

%%
\n          { lines++; chars++; }         
[a-zA-Z0-9]+ { words++; chars += yyleng; }  
.           { chars++; }                   
%%

int yywrap()
{
    return 1;
}

int main()
{
    printf("Enter the text (Press Ctrl+D to stop):\n");
    yylex();
    
    // Display the final results
    printf("\n");
    printf("Lines      : %d\n", lines);
    printf("Words      : %d\n", words);
    printf("Characters : %d\n", chars);
    
    return 0;
}

