#pragma once
#include "tokens.h"
#include "generic_vector.h"

typedef struct mps_exp_node {
    mps_token token;
    int precedence;
    struct mps_exp_node* parent;
    struct mps_exp_node* lhs;
    struct mps_exp_node* rhs;
} mps_exp_node;

typedef mps_exp_node* mps_exp_node_ptr;
declare_vector(mps_exp_node_ptr)

mps_exp_node* mps_make_tree(const vector_mps_token* vec);
mps_exp_node* mps_make_node(const mps_token* begin, const mps_token* end);
void mps_delete_tree(mps_exp_node* tree);