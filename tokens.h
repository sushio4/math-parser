#pragma once
#include <string.h>

#define MAX_TOKEN_STR_SIZE 16

typedef enum mps_token_type {
    empty,
    constant,
    variable,
    operation,
    function,
    openbracket,
    closebracket,
    comma
} mps_token_type;

typedef enum mps_functions {
    sqrt,
    sin,
    cos,
    tan,
    pow
} mps_functions;

static const char* mps_func_names[] = {
    "sqrt",
    "sin",
    "cos",
    "tan",
    "pow"
};

static const char* mps_operators = "+-*/^";

static const int mps_func_num = (sizeof(mps_func_names) / sizeof(mps_func_names[0]));

typedef struct mps_token{
    mps_token_type type;
    mps_functions func;
    double val;
    char op;
    char var_name[MAX_TOKEN_STR_SIZE];
} mps_token;

//static initialization makes it zero so the type is empty
static const mps_token empty_token;

mps_token mps_make_token(const char* str);