%{
void yyerror(char *);
#define YYSTYPE long long int
#include <stdio.h>
#include <string.h>
%}

%token num
%left PLUS

%%
input:
  num PLUS num {}
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
