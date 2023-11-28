#include <stdio.h>
#include "exp_tree_debug.h"

int main() {
    char* tokens = "tan(x*2 + pow(3,x) * sin(x*x/2))";
    printf("Input: %s\n\n", tokens);
    vector_mps_token vec = new_vector_mps_token();
    mps_tokenize(tokens, &vec);

    mps_ast tree;
    mps_make_tree(&vec, &tree);
    mps_display_tree(&tree);

    mps_delete_tree(&tree);
    vector_mps_token_delete(&vec);

    return 0;
}