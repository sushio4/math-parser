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

double mps_eval(const mps_ast* tree, int var_count, mps_variable* vars) {
    
}