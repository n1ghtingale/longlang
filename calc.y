
%{
  #include <math.h>
  #include <stdio.h>
	#include <syntax.h>
#include <stach.h>
  	Stack *s = stack_new();
 	 void yyerror (char const *);
	
%}

// declare token
/* Bison declarations.  */
%define api.value.type {long long} // change double to long long 
%token LINE,STMT,CONST,EXE,IFSTMT,FORSTMT,newL,show,showH,var,if,for,to
%left '-' '+' // left association (reduce left first)
%left '*' '/' '%' // \ is control character 
// deepest is the most important 


%% /* The grammar follows.  */

//we look these grammar together
EXP : CONST newL {   
            stack_push(s, immediate_new(atoi($1));
          
        } ;

%%

void yyerror (char const * a){
	
}

 
void main(){
	printf(">hello longlang> ");
	yyparse();
}
