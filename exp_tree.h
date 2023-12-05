#pragma once
#include "tokens.h"
#include "generic_vector.h"

typedef struct mps_exp_node {
    mps_token token;
    struct mps_exp_node* parent;
    struct mps_exp_node* lhs;
    struct mps_exp_node* rhs;
} mps_exp_node;

static const mps_exp_node mps_empty_exp_node;

declare_vector(mps_exp_node)

typedef struct mps_ast {
    int depth;
    vector_mps_exp_node data;
    mps_exp_node* root;
} mps_ast;

int mps_make_tree(const vector_mps_token* vec, mps_ast* ast);
mps_exp_node* mps_make_node(const mps_token* begin, const mps_token* end, mps_ast* ast);

void mps_delete_tree(mps_ast* tree);