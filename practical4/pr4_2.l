%{
#include <stdio.h>
%}

%%
[c|C]harusat   { printf(" university "); }
[a-zA-Z0-9] {printf("%s",yytext);}
\n      {return 0;}
%%

int main() {
    printf("Enter input: \n");
    yylex();
    return 0;
}

int yywrap() {
    return 1;
}
