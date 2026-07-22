%{
#include <stdio.h>
#include <stdlib.h>

void yyerror(const char *s);
int yylex();
%}

%token DIGIT ID NL

%left '+' '-'
%left '*' '/'

%%

stmt : exp NL
     {
         printf("Valid Expression\n");
         return 0;
     }
     ;

exp : exp '+' exp
    | exp '-' exp
    | exp '*' exp
    | exp '/' exp
    | '(' exp ')'
    | ID
    | DIGIT
    ;

%%

void yyerror(const char *s)
{
    printf("Invalid Expression\n");
}

int main()
{
    printf("Enter Expression: ");
    yyparse();
    return 0;
}
