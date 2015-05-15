#ifndef LONGLANG_SYNTAX_HEADER
#define LONGLANG_SYNTAX_HEADER

#include "list.h"

typedef enum
{
    IMMEDIATE,
    VARIABLE,
    BINARY_OPERATOR,
    INPUT,
    ASSIGNMENT,
    IF_STATEMENT,
    SHOW_STATEMENT,
    MINUS,
    FOR_STATEMENT
} SyntaxType;


typedef struct Immediate { 
    int value; 
} Immediate;

typedef struct Variable {
  int var_index;
} Variable;

typedef enum
{
    ADDITION,
    SUBTRACTION,
    MULTIPLICATION,
    DIVISION,
    MOD,
    COMPARISION
} BinaryExpressionType;

typedef struct Syntax Syntax;

typedef struct BinaryExpression
{
    BinaryExpressionType binary_type;
    Syntax *left;
    Syntax *right;
} BinaryExpression;

typedef struct Assignment
{
    int var_index;
    Syntax* expression;
} Assignment;

typedef struct ForStatement{
    Syntax* startNum;
    Syntax* stopNum;
    Syntax* expression;
} ForStatement;

typedef struct IfStatement {
    Syntax *condition;
    Syntax *then;
} IfStatement;

typedef struct ShowStatement {
    char decOrHex;
    Syntax* var;
}ShowStatement;

typedef struct Minus {
    Syntax* expression;
}Minus;

typedef struct Input { List *lines; } Input;


struct Syntax 
{
    SyntaxType type;
    union {
        Immediate* immediate;
        BinaryExpression* binary_expression;
        Assignment* assignment;
        IfStatement *if_statement;
        ShowStatement *show_statement;
        Minus *minus;
        ForStatement* for_statement;
        Variable *variable;
        Input *input;
    };
};

#endif

