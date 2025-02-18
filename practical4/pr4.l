%{
#include <stdio.h>
int count = 0;
%}

%%
[0-9]+  { count++; printf("%s \n",yytext); }
.       { }
\n      {return 0;}
%%

int main() {
    printf("Enter input: \n");
    yylex();
    printf("Number count: %d\n", count);
    return 0;
}

int yywrap() {
    return 1;
}
