#include <stdio.h>
#include "exp_tree_debug.h"
#include "evaluator.h"

int main() {
    char *tokens = NULL;
    long unsigned int size = 0;
    printf("Enter your equation: ");
    getline(&tokens, &size, stdin);

    vector_mps_token vec = new_vector_mps_token();
    mps_tokenize(tokens, &vec);

    free(tokens);

    mps_ast tree;
    mps_make_tree(&vec, &tree);
    //mps_display_tree(&tree);

    int varc = mps_get_var_count(&tree);
    //printf("Variable amount: %d\n", varc);
    mps_variable* vars = malloc(sizeof(mps_variable) * varc);

    if(mps_get_variables(&tree, vars, varc))
        return -1;
    
    for(int i = 0; i < varc; i++) {
        printf("\nEnter the value for %s: ", vars[i].name);
        scanf("%lf", &vars[i].value);
    }

    printf("Result: %lf\n", mps_eval(&tree, varc, vars));

    mps_delete_tree(&tree);
    vector_mps_token_delete(&vec);
    free(vars);

    return 0;
}