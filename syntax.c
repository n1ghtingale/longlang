#include <stdlib.h>
#include <stdio.h>
#include "syntax.h"

Syntax* immediate_new(int value)
{
    Immediate *immediate = malloc(sizeof(Immediate));
    immediate->value = value;

    Syntax *syntax = malloc(sizeof(Syntax));
    syntax->type = IMMEDIATE;
    syntax->immediate = immediate;

    return syntax;
}

Syntax *if_new(Syntax* im1,Syntax* im2, Syntax *then) {
    IfStatement *if_statement = malloc(sizeof(IfStatement));
    if_statement->immediate1 = im1;
    if_statement->immediate2 = im2;
    if_statement->then = then;

    Syntax *syntax = malloc(sizeof(Syntax));
    syntax->type = IF_STATEMENT;
    syntax->if_statement = if_statement;

    return syntax;
}

Syntax* show_new(char doh,Syntax *varR)
{
    ShowStatement *show_statement = malloc(sizeof(ShowStatement));
    show_statement->decOrHex = doh;
    show_statement->var = varR;

    Syntax *syntax = malloc(sizeof(Syntax));
    syntax->type = SHOW_STATEMENT;
    syntax->show_statement = show_statement;
    return syntax;
}

Syntax* minus_new(Syntax *express)
{
    Minus *minus = malloc(sizeof(Minus));
    minus->expression = express ;

    Syntax *syntax = malloc(sizeof(Syntax));
    syntax->type = MINUS;
    syntax->minus = minus;
    return syntax;
}

Syntax* for_new(Syntax *start,Syntax *stop,Syntax* express)
{
    ForStatement * for_statement = malloc(sizeof(ForStatement));
    for_statement->expression = express ;
    for_statement->startNum = stop;
    for_statement->stopNum = start ;

    Syntax *syntax = malloc(sizeof(Syntax));
    syntax->type = FOR_STATEMENT;
    syntax->for_statement = for_statement;
    return syntax;
}

Syntax* addition_new(Syntax *left, Syntax *right)
{
    BinaryExpression *binary_syntax = malloc(sizeof(BinaryExpression));
    binary_syntax->binary_type = ADDITION;
    binary_syntax->left = left;
    binary_syntax->right = right;

    Syntax *syntax = malloc(sizeof(Syntax));
    syntax->type = BINARY_OPERATOR;
    syntax->binary_expression = binary_syntax;
    return syntax;
}

Syntax* assignment_new(int var_num, Syntax* expression)
{
    Assignment* assignment = malloc(sizeof(Assignment));
    assignment->var_num = var_num;
    assignment->expression = expression;
    Syntax* syntax = malloc(sizeof(Syntax));

    syntax->type = ASSIGNMENT;
    syntax->assignment = assignment;
    return syntax;
}

Syntax* subtraction_new(Syntax *left, Syntax *right)
{
    BinaryExpression *binary_syntax = malloc(sizeof(BinaryExpression));
    binary_syntax->binary_type = SUBTRACTION;
    binary_syntax->left = left;
    binary_syntax->right = right;

    Syntax *syntax = malloc(sizeof(Syntax));
    syntax->type = BINARY_OPERATOR;
    syntax->binary_expression = binary_syntax;
    return syntax;
}

Syntax* multiplication_new(Syntax *left, Syntax *right)
{
    BinaryExpression *binary_syntax = malloc(sizeof(BinaryExpression));
    binary_syntax->binary_type = MULTIPLICATION;
    binary_syntax->left = left;
    binary_syntax->right = right;

    Syntax *syntax = malloc(sizeof(Syntax));
    syntax->type = BINARY_OPERATOR;
    syntax->binary_expression = binary_syntax;
    return syntax;

}
Syntax* less_than_new(Syntax *left, Syntax *right)
{
    BinaryExpression *binary_syntax = malloc(sizeof(BinaryExpression));
    binary_syntax->binary_type = LESS_THAN;
    binary_syntax->left = left;
    binary_syntax->right = right;

    Syntax *syntax = malloc(sizeof(Syntax));
    syntax->type = BINARY_OPERATOR;
    syntax->binary_expression = binary_syntax;
    return syntax;
}

Syntax* less_than_or_equal_new(Syntax *left, Syntax *right)
{
    BinaryExpression *binary_syntax = malloc(sizeof(BinaryExpression));
    binary_syntax->binary_type = LESS_THAN_OR_EQUAL;
    binary_syntax->left = left;
    binary_syntax->right = right;

    Syntax *syntax = malloc(sizeof(Syntax));
    syntax->type = BINARY_OPERATOR;
    syntax->binary_expression = binary_syntax;
    return syntax;
}

Syntax* mod_new(Syntax *left, Syntax *right)
{
    BinaryExpression *binary_syntax = malloc(sizeof(BinaryExpression));
    binary_syntax->binary_type = MOD;
    binary_syntax->left = left;
    binary_syntax->right = right;

    Syntax *syntax = malloc(sizeof(Syntax));
    syntax->type = BINARY_OPERATOR;
    syntax->binary_expression = binary_syntax;
    return syntax;
}

Syntax* division_new(Syntax *left, Syntax *right)
{
    BinaryExpression *binary_syntax = malloc(sizeof(BinaryExpression));
    binary_syntax->binary_type = DIVISION;
    binary_syntax->left = left;
    binary_syntax->right = right;

    Syntax *syntax = malloc(sizeof(Syntax));
    syntax->type = BINARY_OPERATOR;
    syntax->binary_expression = binary_syntax;
    return syntax;
}


