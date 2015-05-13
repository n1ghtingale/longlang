
%{
  #include <math.h>
  #include <stdio.h>
  #include "syntax.h"
  #include "stack.h"

  Stack *s;
  void yyerror (char const *);
  void printExpression(Syntax *);
  void print(Stack *stackPtr);
%}

// declare token
/* Bison declarations.  */
//%define api.value.type {long long} // change double to long long 
%token LINE STMT CONST EXE IFSTMT FORSTMT newL show showH var to eql FOR IF NUM wrong
%left '-' '+' // left association (reduce left first)
%left '*' '/' '%' // \ is control character 
// deepest is the most important 


%% /* The grammar follows.  */

//we look these grammar together
EXP : CONST {
			printf("case constant\n");   
			Syntax *tmp_syntax = (Syntax*) immediate_new($1);
            stack_push(s, tmp_syntax);
          	print(s);
        }
         | EXP '+' EXP {
         	printf("case addition\n");
            Syntax *right = (Syntax *) stack_pop(s);
            Syntax *left = (Syntax *) stack_pop(s);

          
            printf("before push");
            stack_push(s, (Syntax *) addition_new(left, right));
            printf("after push");
            print(s);
            printf("finish addition");
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
				printf("%s",synNow->assignment->var_name);
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
				printf("%s",ss->assignment->var_name);
				printf("=");

				break;
		}
}

 
void main(){
	printf(">hello longlang>\n");
	s = stack_new();
	yyparse();
}
