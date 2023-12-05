#include <math.h>
#include "evaluator.h"

int mps_get_var_count(const mps_ast* tree) {
    char* names[tree->data.size];
    int namec = 0;

    for(mps_exp_node* ptr = tree->data.ptr;
        ptr < (tree->data.ptr + tree->data.size);
        ptr++) {
        
        if(ptr->token.type != tok_variable) continue;

        //check whether the name's on the list
        bool on_list = false;
        for(char** n = names; n < (names + namec); n++) {
            if(strcmp(*n, ptr->token.var_name) == 0) {
                on_list = true;
                break;
            }
        }

        if(on_list) continue;
        //if it's not on the list, add it to the list
        names[namec] = ptr->token.var_name;
        namec++;
    }
    return namec;
}

int mps_get_variables(const mps_ast* tree, mps_variable* vars, int max_vars) {
    int varc = 0;

    for(mps_exp_node* ptr = tree->data.ptr;
        ptr < (tree->data.ptr + tree->data.size);
        ptr++) {
        
        if(varc > max_vars) return -1;

        if(ptr->token.type != tok_variable) continue;

        //check whether the name's on the list
        bool on_list = false;
        for(mps_variable* v = vars; v < (vars + varc); v++) {
            if(strcmp(v->name, ptr->token.var_name) == 0) {
                on_list = true;
                break;
            }
        }

        if(on_list) continue;
        //if it's not on the list, add it to the list
        strcpy(vars[varc].name, ptr->token.var_name);
        varc++;
    }
    return 0;
}

double mps_eval_helper(const mps_exp_node* ptr, int var_count, mps_variable* vars) {
    if(ptr->token.type == tok_constant) 
        return ptr->token.val;

    if(ptr->token.type == tok_variable) {
        for(int i = 0; i < var_count; i++)
            if(strcmp(ptr->token.var_name, vars[i].name) == 0)
                return vars[i].value;
        //not found: error, return NaN
        return NAN;
    }

    if(ptr->token.type == tok_operation) {
        switch (ptr->token.op)
        {
        case '+':
            return mps_eval_helper(ptr->lhs, var_count, vars) + mps_eval_helper(ptr->rhs, var_count, vars);
            break;

        case '-':
            if(ptr->rhs)
                return mps_eval_helper(ptr->lhs, var_count, vars) - mps_eval_helper(ptr->rhs, var_count, vars);
            return - mps_eval_helper(ptr->lhs, var_count, vars);
            break;

        case '*':
            return mps_eval_helper(ptr->lhs, var_count, vars) * mps_eval_helper(ptr->rhs, var_count, vars);
            break;
        
        case '/':
            return mps_eval_helper(ptr->lhs, var_count, vars) + mps_eval_helper(ptr->rhs, var_count, vars);
            break;

        default:
            return NAN;
            break;
        }
    }

    if(ptr->token.type == tok_function) {
        //1 arg
        if(ptr->token.func < func_pow && ptr->token.func >= 0) {
            double val = mps_eval_helper(ptr->lhs, var_count, vars);
            
            typedef double(*func1arg)(double);
            static const func1arg functions[] = {sqrt, sin, cos, tan};
            return functions[ptr->token.func](val);
        }
        //2 arg
        if(ptr->token.func < 5 && ptr->token.func >= func_pow) {
            mps_exp_node* comma = ptr->lhs;
            if(comma->token.type != tok_operation ||
                 comma->token.op != ',')
                return NAN;

            double val0 = mps_eval_helper(comma->lhs, var_count, vars);
            double val1 = mps_eval_helper(comma->rhs, var_count, vars);

            typedef double(*func2arg)(double, double);
            static const func2arg functions[] = {pow};
            int index = ptr->token.func - func_pow;
            return functions[index](val0, val1);
        }
        return NAN;
    }

    return NAN;
}
