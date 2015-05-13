%{
void yyerror(char *);
#define YYSTYPE long long int
#include <stdio.h>
#include <string.h>
%}

%token num LINE var EXP STMT newL
%left PLUS

%%
LINE:
    newL
    | STMT newL
;
EXP:
   CONST
   | EXP + EXP
;
CONST:
     var | num
;
STMT:
    EXP
;

%%
int main(int argc, char *argv[])
{
 while(yyparse());
 return 0;
}

void yyerror(char *e)
{
  printf("--- Error --- %s\n", e);
}
