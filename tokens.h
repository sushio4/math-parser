#pragma once
#include <string.h>
#include "generic_vector.h"

#define MAX_TOKEN_STR_SIZE 16

//masks for tokenizing
#define CONST_MASK 1
#define VAR_MASK 2
#define FUNC_MASK 4
#define OP_MASK 8
#define OPENBRAC_MASK 16
#define CLOSEBRAC_MASK 32
#define COMMA_MASK 64
#define ALL_MASK 127


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

static const int mps_func_num = (sizeof(mps_func_names) / sizeof(mps_func_names[0]));

typedef struct mps_token{
    mps_token_type type;
    mps_functions func;
    double val;
    char op;
    char var_name[MAX_TOKEN_STR_SIZE];
} mps_token;

declare_vector(mps_token)

//static initialization makes it zero so the type is empty
static const mps_token empty_token;

//if candidates == 0 it checks for all possible
mps_token mps_make_token(const char* str, unsigned char candidates);
int mps_tokenize(const char* str, vector_mps_token* token_vector);