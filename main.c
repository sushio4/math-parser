#include <stdio.h>
#include "exp_tree_debug.h"
#include "evaluator.h"

int main() {
    char* tokens = "tan(x*2 + pow(3,x) * sin(x*x/2))";
    printf("Input: %s\n\n", tokens);
    
    vector_mps_token vec = new_vector_mps_token();
    mps_tokenize(tokens, &vec);

    mps_ast tree;
    mps_make_tree(&vec, &tree);
    mps_display_tree(&tree);

    int varc = mps_get_var_count(&tree);
    printf("Variable amount: %d\n", varc);
    mps_variable* vars = malloc(sizeof(mps_variable) * varc);

    if(mps_get_variables(&tree, vars, varc))
        return -1;
    
    for(int i = 0; i < varc; i++) {
        printf("\nEnter the value for %s: ", vars[i].name);
        scanf("%lf", &vars[i].value);
    }



    mps_delete_tree(&tree);
    vector_mps_token_delete(&vec);
    free(vars);

    return 0;
}