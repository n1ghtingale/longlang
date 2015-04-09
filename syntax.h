#ifndef LONGLANG_SYNTAX_HEADER
#define LONGLANG_SYNTAX_HEADER

typedef enum
{
    IMMEDIATE,
    BINARY_OPERATOR
} SyntaxType;


typedef struct Immediate { int value; } Immediate;

typedef enum
{
    ADDITION,
    SUBTRACTION,
    MULTIPLICATION,
    LESS_THAN,
    LESS_THAN_OR_EQUAL
} BinaryExpressionType;

typedef struct Syntax Syntax;

typedef struct BinaryExpression
{
    BinaryExpressionType binary_type;
    Syntax *left;
    Syntax *right;
} BinaryExpression;

struct Syntax 
{
    SyntaxType type;
    union {
        Immediate* immediate;
        BinaryExpression* binary_expression;
    };
};

#endif
