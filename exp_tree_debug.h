#pragma once
#include "exp_tree.h"
#include "token_debug.h"

void mps_display_tree(mps_exp_node* tree) {
    vector_mps_exp_node_ptr vec = new_vector_mps_exp_node_ptr();
    if(tree == NULL) return;
    vector_mps_exp_node_ptr_push(&vec, tree);
    //traverse the tree and save all the pointers to the vector
    //those keep track of which nodes save the lhs/rhs pointers
    int i0 = 0, i1 = 1;
    bool loop = true;
    int gen = 0;
    while(loop) {
        printf("Generation: %d\n", gen);
        //save ptr of all children if not null
        int count = 0;
        for(int i = i0; i < i1; i++){
            if(vec.ptr[i]->lhs){
                vector_mps_exp_node_ptr_push(&vec, vec.ptr[i]->lhs);
                count++;
            }
            if(vec.ptr[i]->rhs){
                vector_mps_exp_node_ptr_push(&vec, vec.ptr[i]->rhs);
                count++;
            }
            //display the parent
            mps_display_token(vec.ptr[i]->token);
            printf("lhs = %d, rhs = %d\n\n", (vec.ptr[i]->lhs != 0), (vec.ptr[i]->rhs != 0));
        }
        i0 = i1;
        i1 += count;
        loop = (count != 0);
        gen++;
    }
    vector_mps_exp_node_ptr_delete(&vec);
}

void mps_display_tree_pretty(mps_exp_node* tree) {
    vector_mps_exp_node_ptr vec = new_vector_mps_exp_node_ptr();
    if(tree == NULL) return;
    vector_mps_exp_node_ptr_push(&vec, tree);
    //traverse the tree and save all the pointers to the vector
    //those keep track of which nodes save the lhs/rhs pointers
    int i0 = 0, i1 = 1;
    bool loop = true;
    int gen = 0;
    while(loop) {
        //save ptr of all children if not null
        int count = 0;
        for(int i = i0; i < i1; i++){
            if(vec.ptr[i]->lhs){
                vector_mps_exp_node_ptr_push(&vec, vec.ptr[i]->lhs);
                count++;
            }
            if(vec.ptr[i]->rhs){
                vector_mps_exp_node_ptr_push(&vec, vec.ptr[i]->rhs);
                count++;
            }
            //display the parent
            mps_display_token(vec.ptr[i]->token);
            printf("lhs = %d, rhs = %d\n\n", (vec.ptr[i]->lhs != 0), (vec.ptr[i]->rhs != 0));
        }
        i0 = i1;
        i1 += count;
        loop = (count != 0);
        gen++;
    }
    vector_mps_exp_node_ptr_delete(&vec);
}