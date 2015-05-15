
%{
  #include <math.h>
  #include <stdio.h>
  #include "syntax.h"
  #include "stack.h"

  
  int variable[26];

  #include "assembly.h"


  Stack *s;
  void yyerror (char const *);
  void printExpression(Syntax *);
  void print(Stack *stackPtr);
%}

// declare token
/* Bison declarations.  */
//%define api.value.type {long long} // change double to long long 
%token NEWL SHOW SHOWH VAR TO EQL FOR IF NUM WRONG
%left '-' '+' // left association (reduce left first)
%left '*' '/' '%' // \ is control character 
// deepest is the most important 


%% /* The grammar follows.  */
STMT :  %empty | LINE NEWL | IFSTMT NEWL | FORSTMT | EXP | NEWL;

//we look these grammar together
LINE :	VAR '=' EXP  {
	    printf("case assignment\n");
	    Syntax *exp_to_push = (Syntax *) stack_pop(s);
	    Syntax *ass_to_push = (Syntax*)assignment_new($1, exp_to_push);
	    stack_push(s, ass_to_push);
	}
	| SHOW VAR {
		// keep index
	    printf("case show\n");
	    Syntax *tmp_var = (Syntax *) stack_pop(s);
	    Syntax *show_to_push = (Syntax*) show_new('d',tmp_var);
	    stack_push(s, show_to_push);
	}
	| SHOWH VAR {
	    printf("case showH\n");
	    // keep index
	    Syntax *tmp_var = (Syntax *) stack_pop(s);
	    Syntax *show_to_push = (Syntax*) show_new('h',tmp_var);
	    stack_push(s, show_to_push);
	} 
	
;

IFSTMT :  IF '(' CONST EQL CONST ')' LINE {
	    printf("case if\n");
	    Syntax *then = (Syntax *) stack_pop(s);
	    Syntax *tmp_syntax2 = (Syntax*)stack_pop(s);
	    Syntax *tmp_syntax1 = (Syntax*)stack_pop(s);
	    Syntax *tmp_syntax_push = (Syntax*) if_new(tmp_syntax1,tmp_syntax2,then);
	    stack_push(s, tmp_syntax_push);
	};
FORSTMT : FOR '(' NUM TO NUM ')' LINE {
	    printf("case for\n");
	    Syntax *to_do = (Syntax*)stack_pop(s);
	    Syntax *stop_num = (Syntax*)stack_pop(s);
	    Syntax *start_num = (Syntax*)stack_pop(s);
	    Syntax *for_push = (Syntax*) for_new(start_num,stop_num,to_do);
	    stack_push(s,for_push);
	};
EXP : CONST {
	    printf("case constant\n");   
	    //Syntax *tmp_syntax = (Syntax*) immediate_new($1);
            //stack_push(s, tmp_syntax);
            //printf("value: %d\n", tmp_syntax->immediate->value);
            //print(s);
        }
         | EXP '+' EXP {
            printf("case addition\n");
            Syntax *right = (Syntax *) stack_pop(s);
            Syntax *left = (Syntax *) stack_pop(s);
            stack_push(s, (Syntax *) addition_new(left, right)); 
        }  

       | EXP '-' EXP {
       	    printf("case -\n");
            Syntax *right = (Syntax *) stack_pop(s);
            Syntax *left = (Syntax *) stack_pop(s);
            stack_push(s, (Syntax *) subtraction_new(left, right));
       }

       | EXP '*' EXP {
       	    printf("case multiply\n");
            Syntax *right = (Syntax *) stack_pop(s);
            Syntax *left =  (Syntax *) stack_pop(s);
            stack_push(s, (Syntax *) multiplication_new(left, right));
       }

       | EXP '/' EXP {
       	    printf("case division\n");
            Syntax *right = (Syntax *) stack_pop(s);
            Syntax *left = (Syntax *) stack_pop(s);
            stack_push(s, (Syntax *) division_new(left, right));
       }

       | EXP '%' EXP {
       	    printf("case mod\n");
            Syntax *right = (Syntax *) stack_pop(s);
            Syntax *left = (Syntax *) stack_pop(s);
            stack_push(s, (Syntax *) mod_new(left, right));
       } ;

       | '-' EXP {
       	    printf("case minus\n");
       	    Syntax *expression_push = (Syntax *) stack_pop(s);
       	    stack_push(s, (Syntax *) minus_new(expression_push));
       }

       | '(' EXP ')'{
       	    printf("case parenthesis\n");

       };
 
 	CONST : VAR {
 	    printf("case var\n");
 	    Syntax *tmp_syntax = (Syntax*) variable_new($1);
 	    stack_push(s, tmp_syntax);
	}

	| NUM {
	    printf("case num\n");
	    Syntax *tmp_syntax = (Syntax*) immediate_new($1);
	    printf("value: %d\n", tmp_syntax->immediate->value);
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
				printf("%d",synNow->assignment->var_index);
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
				printf("%d",ss->assignment->var_index);
				printf("=");

				break;
		}
}

 
void main(){
	printf(">hello longlang>\n");
	s = stack_new();
	yyparse();
	//print(s);	
	write_assembly((Syntax *) stack_pop(s));
}