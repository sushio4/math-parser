#include "tokens.h"
#include <stdio.h>

static const char* mps_token_type_names[] = {
    "empty",
    "constant",
    "variable",
    "operation",
    "function",
    "openbracket",
    "closebracket",
    "comma"
};

void mps_display_token(mps_token token) {
    printf("type: %s, ", mps_token_type_names[token.type]);
    switch (token.type)
    {
    case tok_constant:
        printf("val = %f\n", token.val);
        break;
    case tok_variable:
        printf("var_name: %s\n", token.var_name);
        break;
    case tok_operation:
        printf("'%c'\n", token.op);
        break;
    case tok_function:
        printf("func: %s\n", mps_func_names[token.func]);
        break;
    case tok_openbracket:
        printf("'('\n");
        break;
    case tok_closebracket:
        printf("')'\n");
        break;
    case tok_comma:
        printf("','\n");
        break;
    default:
        break;
    }
}

void mps_display_token_less(mps_token token) {
    switch (token.type)
    {
    case tok_constant:
        printf("%f", token.val);
        break;
    case tok_variable:
        printf("%s", token.var_name);
        break;
    case tok_operation:
        printf("%c", token.op);
        break;
    case tok_function:
        printf("%s", mps_func_names[token.func]);
        break;
    case tok_openbracket:
        printf("(");
        break;
    case tok_closebracket:
        printf(")");
        break;
    case tok_comma:
        printf(",");
        break;
    default:
        break;
    }
}