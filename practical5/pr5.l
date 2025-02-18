%{
#include <stdio.h>
#include <string.h>
#define KEYWORD      1
#define IDENTIFIER   2
#define CONSTANT     3
#define OPERATOR     4
#define PUNCTUATION  5

void print_token(const char* type, const char* value) {
    printf("Token: %-12s Value: %s\n", type, value);
}

%}

DIGIT       [0-9]
LETTER      [a-zA-Z_]
ALPHANUM    ({LETTER}|{DIGIT})
IDENTIFIER  {LETTER}{ALPHANUM}*
INT_CONST   {DIGIT}+
FLOAT_CONST {DIGIT}+"."{DIGIT}*
OPERATOR    "+"|"-"|"*"|"/"|"="|"=="|"!="|"<"|">"|"<="|">="|"&&"|"||"|"!"
PUNCTUATION ";"|","|"("|")"|"{"|"}"|"["|"]"

%%

"//".*      ; // Skip single-line comments
"/*"        { BEGIN(COMMENT); } // Start of multi-line comment
<COMMENT>"*/" { BEGIN(INITIAL); } // End of multi-line comment
<COMMENT>\n   ; // Skip newlines inside multi-line comments
<COMMENT>.    ; // Skip any character inside multi-line comments

"auto"|"break"|"case"|"char"|"const"|"continue"|"default"|"do"|"double"|"else"|"enum"|"extern"|"float"|"for"|"goto"|"if"|"int"|"long"|"register"|"return"|"short"|"signed"|"sizeof"|"static"|"struct"|"switch"|"typedef"|"union"|"unsigned"|"void"|"volatile"|"while" {
    print_token("KEYWORD", yytext);
}

{IDENTIFIER} {
    print_token("IDENTIFIER", yytext);
}

{INT_CONST}|{FLOAT_CONST} {
    print_token("CONSTANT", yytext);
}

{OPERATOR} {
    print_token("OPERATOR", yytext);
}

{PUNCTUATION} {
    print_token("PUNCTUATION", yytext);
}

[ \t\n]+   ;

. {
    printf("Error: Unrecognized character '%s'\n", yytext);
}

%%

int main() {
    FILE *file;
    file = fopen("test1.c","r");
    if(!file){
              printf("Error");
    }
    yyin = file;
    yylex();

    fclose(yyin);

    return 0;
}
int yywrap() {}

