%{
void yyerror(char *);
#define YYSTYPE long long int
#include <stdio.h>
#include <string.h>
struct instruction
{
  //refactor later. T_T
  char operator[20];
  char operand1[20];
  char operand2[20];
};
//limit at 50 instructions now. ;_;
struct instruction instructions[50];
int offset=0;
%}

%token num
%left PLUS

%%
input:
  num PLUS num { strcpy mov	DWORD PTR [esp+28]}
;

%%
int main(int argc, char *argv[])
{
 while(yyparse());
 
 //start generate assembly code, will move into seperate function later. 
 //don't have to worry about meaning of codes below, just some initialization.
 printf("\t.file\t\"\%s\"\n", argv[1]);
 printf("\t.intel_syntax noprefix\n");
 printf("\t.def	___main;	.scl	2;	.type	32;	.endef\n");
 printf("\t.section .rdata,\"dr\"\n");
 printf("LC0:\n");
 printf("\t.ascii \"%%d\\12\\0\n\"\n");
 printf("\t.text\n");
 printf("\t.globl	_main\n");
 printf(".def	_main;	.scl	2;	.type	32;	.endef\n");
 printf("_main:\n");
 printf("LFB10:\n");
 printf("\t.cfi_startproc\n");
 printf("\tpush	ebp\n");
 printf("\tcfi_def_cfa_offset 8\n");
 printf("\t.cfi_offset 5, -8\n");
 printf("\tmov	ebp, esp\n");
 printf("\t.cfi_def_cfa_register 5");
 printf("\tand	esp, -16\n");
 printf("\tsub	esp, 32\n");
 printf("\tcall	___main\n");
 //assembly code of our language start here. :3
 printf("\tmov	DWORD PTR [esp+28], 1\n");
 printf("\tmov	DWORD PTR [esp+24], 2\n");
 printf("\tmov	eax, DWORD PTR [esp+24]\n");
 printf("\tmov	edx, DWORD PTR [esp+28]\n");
 printf("\tadd	eax, edx\n");
 printf("\tmov	DWORD PTR [esp+4], eax\n");
 printf("\tmov	DWORD PTR [esp], OFFSET FLAT:LC0\n");
 printf("\tcall	_printf\n");
 printf("\tmov	eax, 0\n");
 printf("\tleave\n");
 printf("\t.cfi_restore 5\n");
 printf("\t.cfi_def_cfa 4, 4\n");
 printf("\tret\n");
 printf("\t.cfi_endproc\n");
 printf("LFE10:\n");
 printf("\t.ident	\"GCC: (GNU) 4.8.1\"\n");
 printf("\t.def	_printf;	.scl	2;	.type	32;	.endef\n");
 return 0;
}

void yyerror(char *e)
{
  printf("--- Error --- %s\n", e);
}