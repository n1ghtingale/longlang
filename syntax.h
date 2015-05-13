#ifndef LONGLANG_SYNTAX_HEADER
#define LONGLANG_SYNTAX_HEADER

typedef enum
{
    IMMEDIATE,
    BINARY_OPERATOR,
    ASSIGNMENT,
    IF_STATEMENT,
    SHOW_STATEMENT,
    MINUS,
    FOR_STATEMENT
} SyntaxType;


typedef struct Immediate { int value; } Immediate;

typedef enum
{
    ADDITION,
    SUBTRACTION,
    MULTIPLICATION,
    LESS_THAN,
    LESS_THAN_OR_EQUAL,
    DIVISION,
    MOD,
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
    int var_num;
    Syntax* expression;
} Assignment;

typedef struct ForStatement{
    Syntax* startNum;
    Syntax* stopNum;
    Syntax* expression;
} ForStatement;

typedef struct IfStatement {
    Syntax* immediate1;
    Syntax* immediate2;
    Syntax *then;
} IfStatement;

typedef struct ShowStatement {
    char decOrHex;
    Syntax* var;
}ShowStatement;

typedef struct Minus {
    Syntax* expression;
}Minus;

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
    };
};  


#endif

