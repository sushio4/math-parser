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
    case constant:
        printf("val = %f\n", token.val);
        break;
    case variable:
        printf("var_name: %s\n", token.var_name);
        break;
    case operation:
        printf("'%c'\n", token.op);
        break;
    case function:
        printf("func: %s\n", mps_func_names[token.func]);
        break;
    case openbracket:
        printf("'('\n");
        break;
    case closebracket:
        printf("')'\n");
        break;
    case comma:
        printf("','\n");
        break;
    default:
        break;
    }
}