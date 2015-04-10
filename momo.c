void print(Stack *stackPtr){

	// the new stack will have everything in the old one
	Stack *newStack;
	while(!stack_isFree(stackPtr)){
		stack_push(newStack,stack_pop(stackPtr));
	}
	
	while(!stack_isFree(newStack)){
		Syntax * synNow = stack_pop(newStack);

		switch(synNow->type){
			case IMMEDIATE:
				printf("%d",synNow->immediate->value);
				break;

			case BINARY_OPERATOR:

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
				printf("");
				printf("");
				printf("");
				break;

			case ASSIGNMENT:
				printf("%s",synNow->assignment->var_name);
				printf("=");

				break;
		}

	}
}

