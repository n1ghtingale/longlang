#include <stdlib.h>
#include "stack.h"
#include "list.h"
#include "syntax.h"
#include <stdio.h>

void printExpression(Syntax *);

void print(Stack *stackPtr){
	printf("start print\n");
	Syntax *synNow;
	Stack *saveOld;
	// the new stack will have everything in the old one
	Stack *newStack;
	while(!stack_empty(stackPtr)){
		stack_push(newStack,(Syntax *)stack_pop(stackPtr));
	}
	
	printf("reverse stack complete\n");

	while(!stack_empty(newStack)){
		synNow = (Syntax *) stack_pop(newStack);
		printf("start to check\n");
		switch(synNow->type){
			printf("in switch case in Print function\n");
			case IMMEDIATE:
				printf("%d",synNow->immediate->value);
				Syntax *to_push = (Syntax*) immediate_new(synNow->immediate->value);
				stack_push(saveOld,(Syntax*)to_push);
				break;

			case BINARY_OPERATOR:
				stack_push(saveOld, (Syntax *) addition_new(synNow->binary_expression->left, synNow->binary_expression->right));

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

				Syntax *to_push_assign = (Syntax*) assignment_new(synNow->assignment->var_name,synNow->assignment->expression);
				stack_push(saveOld,(Syntax*)to_push_assign);
				break;
		}
	}
	printf("why");
}

void printExpression(Syntax *ss){
	printf("start print expression");
	switch(ss->type){
		printf("in switch");
		
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
	Stack* s = stack_new();
	Syntax *left = (Syntax*) immediate_new(3);
	Syntax *right = (Syntax*) immediate_new(2);
	//Syntax *left_most = (Syntax*) immediate_new(1); 
	Syntax *binary = (Syntax*)addition_new(left, right);
	//Syntax *binary2 = (Syntax*) addition_new(left_most, binary);

    stack_push(s,(Syntax*)binary);
	print(s);
	printf("dadada");
	return 0;
}
