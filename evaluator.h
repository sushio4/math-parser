#pragma once
#include "exp_tree.h"

typedef struct mps_variable {
    double value;
    char name[MAX_TOKEN_STR_SIZE];
} mps_variable;

int mps_get_var_count(const mps_ast* tree);

//returns 0 on success
int mps_get_variables(const mps_ast* tree, mps_variable* vars, int max_vars);

//evaluates whole tree when given variables, returns NaN of failure
double mps_eval(const mps_ast* tree, int var_count, mps_variable* vars);