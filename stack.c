#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "stack.h"
#include "syntax.h"

Stack *stack_new()
{
    Stack *stack = malloc(sizeof(Stack));
    stack->size = 0;
    stack->content = 0;

    return stack;
}

void stack_free(Stack *stack)
{
    if (stack->size > 0) {
        free(stack->content);
    }
    free(stack);
}

void stack_push(Stack *stack, void *item)
{
    stack->size++;

    stack->content =
        realloc(stack->content, stack->size * sizeof *stack->content);
    stack->content[stack->size - 1] = item;
}

void* stack_pop(Stack *stack)
{
    if(stack->size >= 1){
        stack->size--;

        void *item = stack->content[stack->size];
        stack->content =
            realloc(stack->content, stack->size * sizeof *stack->content);

       //     if()
         //   printf("value left: %d", ((Syntax *) item)->binary_expression->left->immediate->value);
         //   printf("value right: %d", ((Syntax *) item)->binary_expression->right->immediate->value);
       // printf("value: %d", ((Syntax *) item)->binary_expression->left->value);


        return item;
    }
}

void *stack_peek(Stack *stack)
{
    if(stack->size >= 1) 
        return stack->content[stack->size - 1];
}

bool stack_empty(Stack *stack) { return stack->size == 0; }
