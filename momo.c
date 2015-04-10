#include <stdlib.h>
#include "stack.h"
#include "list.h"
#include "syntax.h"
#include <stdio.h>

void printExpression(Syntax *);

void print(Stack *stackPtr){
	Syntax *synNow;
	// the new stack will have everything in the old one
	Stack *newStack;
	// while(!stack_empty(stackPtr)){
	// 	stack_push(newStack,stack_pop(stackPtr));
	// }
	
	while(!stack_empty(stackPtr)){
		synNow = stack_pop(stackPtr);

		switch(synNow->type){
			case IMMEDIATE:
				printf("%d",synNow->immediate->value);
				break;

			case BINARY_OPERATOR:
				//printf("*****%d", synNow->binary_expression->right->type);
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

int main(){
	Stack *s = stack_new();
	Syntax *left = (Syntax*) immediate_new(3);
	Syntax *right = (Syntax*) immediate_new(2);
	Syntax *most = (Syntax*) immediate_new(1); 
	Syntax *binary = (Syntax*)addition_new(left, right);
	Syntax *binary2 = (Syntax*) addition_new(most, binary);
	Syntax *tmp;

	//printf("%d <<<\n", left->immediate->value);
	stack_push(s, binary2);
	tmp = stack_pop(s);
	printf("%d\n====\n", tmp->immediate->value);

	// printExpression(binary);
	// printf("hello\n");
	// printExpression(binary2);
	// printf("\n");
	print(s);
	return 0;
}