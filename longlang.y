
%{
  #include <math.h>
  #include <stdio.h>
  #include "syntax.h"
  #include "stack.h"
  
  int variable[26];

  Stack *s;
  void yyerror (char const *);
  void printExpression(Syntax *);
  void print(Stack *stackPtr);
%}

// declare token
/* Bison declarations.  */
//%define api.value.type {long long} // change double to long long 
%token LINE STMT CONST EXE IFSTMT FORSTMT NEWL SHOW SHOWH VAR TO EQL FOR IF NUM WRONG
%left '-' '+' // left association (reduce left first)
%left '*' '/' '%' // \ is control character 
// deepest is the most important 


%% /* The grammar follows.  */


//we look these grammar together
LINE : NEWL 
	| VAR '=' EXP NEWL {
		Syntax *exp_to_push = (Syntax *) stack_pop(s);
	    stack_push(s, assignment_new($1, exp_to_push));
	}
	| SHOW VAR NEWL{
		// keep index
		Syntax *tmp_var = (Syntax *) stack_pop(s);
		Syntax *show_to_push = (Syntax*) show_new('d',tmp_var);
		stack_push(s, show_to_push);
	}
	| SHOWH VAR NEWL{
		// keep index
		Syntax *tmp_var = (Syntax *) stack_pop(s);
		Syntax *show_to_push = (Syntax*) show_new('h',tmp_var);
		stack_push(s, show_to_push);
	} ;

IFSTMT : IF '(' CONST EQL CONST ')' LINE {
	Syntax *then = (Syntax *) stack_pop(s);
	Syntax *tmp_syntax2 = (Syntax*)stack_pop(s);
	Syntax *tmp_syntax1 = (Syntax*)stack_pop(s);
	Syntax *tmp_syntax_push = (Syntax*) if_new(tmp_syntax1,tmp_syntax2,then);
	stack_push(s, tmp_syntax_push);
};

FORSTMT : FOR '(' NUM TO NUM ')' LINE {
	Syntax *to_do = (Syntax*)stack_pop(s);
	Syntax *stop_num = (Syntax*)stack_pop(s);
	Syntax *start_num = (Syntax*)stack_pop(s);
	Syntax *for_push = (Syntax*) for_new(start_num,stop_num,to_do);
	stack_push(s,for_push);
}
EXP : CONST {
			printf("case constant\n");   
			Syntax *tmp_syntax = (Syntax*) immediate_new($1);
            stack_push(s, tmp_syntax);
          	//print(s);
        }
         | EXP '+' EXP {
         	printf("case addition\n");
            Syntax *right = (Syntax *) stack_pop(s);
            Syntax *left = (Syntax *) stack_pop(s);
            stack_push(s, (Syntax *) addition_new(left, right)); 

         }  

       | EXP '-' EXP {
          Syntax *right = (Syntax *) stack_pop(s);
          Syntax *left = (Syntax *) stack_pop(s);
          stack_push(s, (Syntax *) subtraction_new(left, right));
       }

       | EXP '*' EXP {
          Syntax *right = (Syntax *) stack_pop(s);
          Syntax *left =  (Syntax *) stack_pop(s);
          stack_push(s, (Syntax *) multiplication_new(left, right));
       	  print(s);
       }

       | EXP '/' EXP {
         Syntax *right = (Syntax *) stack_pop(s);
          Syntax *left = (Syntax *) stack_pop(s);
          stack_push(s, (Syntax *) division_new(left, right));
       }

       | EXP '%' EXP {
           Syntax *right = (Syntax *) stack_pop(s);
          Syntax *left = (Syntax *) stack_pop(s);
          stack_push(s, (Syntax *) mod_new(left, right));
       } ;

       | '-' EXP {
       		Syntax *expression_push = (Syntax *) stack_pop(s);
       		stack_push(s, (Syntax *) minus_new(expression_push));
       }

       | '(' EXP ')'{

       };
 
 CONST : VAR {
 			Syntax *tmp_syntax = (Syntax*) immediate_new($1);
 			stack_push(s, tmp_syntax);
		 }

		 | NUM {
		 	Syntax *tmp_syntax = (Syntax*) immediate_new($1);
		 	stack_push(s, tmp_syntax);

		 };



%%

void yyerror (char const * a){
	
}

void print(Stack *stackPtr){
	Syntax *synNow;
	// the new stack will have everything in the old one
	Stack *newStack;
	// while(!stack_empty(stackPtr)){
	// 	stack_push(newStack,stack_pop(stackPtr));
	// }
	
	while(!stack_empty(stackPtr)){
		synNow = (Syntax *) stack_pop(stackPtr);

		switch(synNow->type){
			case IMMEDIATE:
				printf("%d",synNow->immediate->value);
				break;

			case BINARY_OPERATOR:
				printExpression(synNow->binary_expression->left);
				switch(synNow->binary_expression->binary_type){
					case ADDITION:
						printf("+");
						break;
					case SUBTRACTION:
						printf("-");
						break;
					case MULTIPLICATION:
						printf("*");
						break;
				}
				printExpression(synNow->binary_expression->right);
				break;

			case ASSIGNMENT:
				printf("%d",synNow->assignment->var_num);
				printf("=");

				break;
		}
	}
}

void printExpression(Syntax *ss){
	switch(ss->type){
			case IMMEDIATE:
				printf("%d",ss->immediate->value);
				break;

			case BINARY_OPERATOR:
				printExpression(ss->binary_expression->left);
				switch(ss->binary_expression->binary_type){
					case ADDITION:
						printf("+");
						break;
					case SUBTRACTION:
						printf("-");
						break;
					case MULTIPLICATION:
						printf("*");
						break;
				}
				printExpression(ss->binary_expression->right);
				break;

			case ASSIGNMENT:
				printf("%d",ss->assignment->var_num);
				printf("=");

				break;
		}
}

 
void main(){
	printf(">hello longlang>\n");
	s = stack_new();
	yyparse();
}
