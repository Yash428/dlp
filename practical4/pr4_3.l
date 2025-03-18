%{
#include <stdio.h>
#include <stdlib.h>
int wcount = 0;
int lcount = 0;
int ccount = 0;
int tabcount = 0;
int scount = 0;
int idcount = 0;
int opcount = 0;
int spcount = 0;
int digcount = 0;
int intcount = 0;
%}

DIGIT       [0-9]
LETTER      [a-zA-Z]
SPECIAL     "$"|"@"
KEYWORD     "int"|"main"
OPERATOR    "="
SYMBOL      "{"|"}"|"("|")"|";"
ALPHANUM    ({LETTER}|{DIGIT})
ID          [a-zA-Z][a-zA-Z0-9_$@]*
INT_CONST   {DIGIT}+
FLOAT_CONST {DIGIT}+"."{DIGIT}*

%%

{KEYWORD}      {printf("1");
{ID}           {idcount++;}
{SYMBOL}       {;}
{OPERATOR}     {opcount++;}
{SPECIAL}      {spcount++;}
{INT_CONST}    {intcount++;}
\n             {lcount++;}
\t             {tabcount++;}
[ ]          {scount++;}

%%

int main() {
    FILE *file;
    file = fopen("test1.c","r");
    if(!file){
              printf("Error");
    }
    yyin = file;
    yylex();
    printf("\n Practical 4.3\n");
    printf("line count: %d\n", lcount);
    printf("Tab count: %d\n", tabcount);
    printf("Space count: %d\n", scount);
    printf("Identifier count: %d\n", idcount);
    fclose(yyin);
    return 0;
}

int yywrap() {}
