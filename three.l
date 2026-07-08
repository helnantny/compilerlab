%{
#include <stdio.h>
%}

%%
[a-z]   { printf("%c", yytext[0] - 32); } 
.       { printf("%s", yytext); }          
\n      { printf("%s", yytext); }         
%%

int yywrap() {
    return 1;
}

int main() {
    printf("Enter text:\n");
    yylex();
    return 0;
}
