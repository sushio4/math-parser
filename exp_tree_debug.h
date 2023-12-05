#pragma once
#include "exp_tree.h"
#include "token_debug.h"

unsigned int ptr_to_index(const mps_ast* tree, const mps_exp_node* ptr) {
    return (unsigned int)((char*)ptr - (char*)tree->data.ptr) / sizeof(mps_exp_node);
}

void mps_display_tree(mps_ast* tree) {
    if(tree == NULL) return;

    printf("Depth: %d\n\n", tree->depth);

    for(mps_exp_node* ptr = tree->data.ptr; ptr < (tree->data.ptr + tree->data.size); ptr++) {
        printf("Index: %d\n", ptr_to_index(tree, ptr));
        mps_display_token(ptr->token);
        printf("Parent i: %d\nLhs i: %d\nRhs i: %d\n\n", 
            ptr_to_index(tree, ptr->parent) < tree->data.size ? ptr_to_index(tree, ptr->parent) : -1,
            ptr_to_index(tree, ptr->lhs) < tree->data.size ? ptr_to_index(tree, ptr->lhs) : -1,
            ptr_to_index(tree, ptr->rhs) < tree->data.size ? ptr_to_index(tree, ptr->rhs) : -1);
    }
}

void mps_pretty_display_tree(mps_ast* tree) {
    //TODO
}
