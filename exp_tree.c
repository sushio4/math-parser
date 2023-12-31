#include "exp_tree.h"

static inline int max(int a, int b) {
    return a > b ? a : b;
}

define_vector(mps_exp_node)

int mps_get_precedence(char operator) {
    switch(operator) {
        case ',':
            return 1;
        case '+':
        case '-':
            return 2;
        case '*':
        case '/':
            return 3;
        default:
            return 4;
    }
}

int mps_get_depth(const mps_exp_node* node, int prev_depth) {
    prev_depth++;
    int ldepth = 0, rdepth = 0;
    
    if(!node->lhs && !node->rhs)
        return prev_depth;

    if(node->lhs)
        ldepth = mps_get_depth(node->lhs, prev_depth);
    if(node->rhs)
        rdepth = mps_get_depth(node->rhs, prev_depth);
    return max(ldepth, rdepth);
}

//ptr is the pointer to the first open bracket and backref is for saving where it ends
mps_exp_node* parse_bracket_exp(const mps_token *ptr, const mps_token** back_ref, mps_ast* ast)
{
    int brack_count = 1;

    const mps_token *front = ptr + 1;
    const mps_token *back = front;
    for (; brack_count; back++)
    {
        if (back->type == tok_openbracket)
            brack_count++;
        else if (back->type == tok_closebracket)
            brack_count--;
    }

    *back_ref = --back;
    return mps_make_node(front, back, ast);
}

mps_exp_node* mps_make_node(const mps_token* begin, const mps_token* end, mps_ast* ast) {
    mps_exp_node* current = NULL;
    mps_exp_node* root = NULL;
    bool in_brackets = false;

    for(const mps_token* ptr = begin; ptr < end; ptr++) {
        mps_exp_node* new_node;

        if(!ptr->type) continue; 

        if(ptr->type == tok_openbracket) {
            const mps_token* back;
            new_node = parse_bracket_exp(ptr, &back, ast);

            ptr = back;

            if(!current) {
                root = current = new_node;
                in_brackets = true;
            }
            else {
                new_node->parent = current;
                if(current->lhs) 
                    current->rhs = new_node;
                else 
                    current->lhs = new_node;
            }
            continue;
        }

        new_node = (ast->data.ptr + ast->data.size);
        vector_mps_exp_node_push(&ast->data, mps_empty_exp_node);
        new_node->lhs = 
            new_node->rhs = 
            new_node->parent = NULL;
        new_node->token = *ptr;
        
        if(ptr->type == tok_comma) {
            new_node->token.type = tok_operation;
            new_node->token.op = ',';
        }

        if(!current) {
            root = current = new_node;
            continue;
        }

        if(ptr->type == tok_variable ||
            ptr->type == tok_constant) {
            //it's one of the arguments of an operator (or function)
            new_node->parent = current;
            if(current->lhs) 
                current->rhs = new_node;
            else 
                current->lhs = new_node;
            //check if there was unary minus before
            if(current->token.type == tok_operation && current->token.op == '-' &&
                current->parent && current->parent->token.type == tok_operation) {

                current = current->parent;
            }
        }
        else if(ptr->type == tok_function) {
            const mps_token* back;
            mps_exp_node* child = parse_bracket_exp(ptr + 1, &back, ast);
            ptr = back;
            child->parent = new_node;
            new_node->lhs = child;

            new_node->parent = current;
            if(current->lhs) 
                current->rhs = new_node;
            else 
                current->lhs = new_node;                
        }
        else if(new_node->token.type == tok_operation) {
            //check for unary minus
            if(ptr->op == '-' && current->token.type == tok_operation && current->rhs == NULL) {
                current->rhs = new_node;
                new_node->parent = current;
                current = new_node;
                continue;
            }

            if(in_brackets) {
                new_node->lhs = current;
                current->parent = new_node;
                root = current = new_node;
                root->parent = NULL;
                in_brackets = false;

                continue;
            } 

            if(current->token.type != tok_operation) {
                new_node->lhs = current;
                current->parent = new_node;
                current = root = new_node;

                continue;
            }

            //check precedence 
            if(mps_get_precedence(new_node->token.op) > mps_get_precedence(current->token.op)) {
                /*structure:
                    current
                    |   |
                    |   new_node
                */
                if(!current->rhs) {
                    current->rhs = new_node;
                    new_node->parent = current;

                    continue;
                }
                new_node->lhs = current->rhs;
                current->rhs->parent = new_node;
                
                new_node->parent = current;
                current->rhs = new_node;

                current = new_node;
            }
            else { 
                /*structure:        less precedence op (new current->parent)
                    new_node    or      |          |
                    |                  ...      new_node
                    ...                 |
                    |                current
                    current
                    |   |
                */
                //go up in the tree
                while(current->parent && mps_get_precedence(new_node->token.op) <= mps_get_precedence(current->parent->token.op)) {
                    current = current->parent;
                }

                if(current->parent) {
                    current->parent->rhs = new_node;
                    new_node->parent = current->parent;
                }
                else {
                    new_node->lhs = current;
                    current->parent = new_node;
                    root = new_node;
                }
                current = new_node;
            }
        } else {
            return NULL;
        }
    }

    return root;
}

int mps_make_tree(const vector_mps_token* vec, mps_ast* ast) {
    int exp_tokens = 0;
    for(mps_token* ptr = vec->ptr; ptr < (vec->ptr + vec->size); ptr++) {
        if(ptr->type != tok_openbracket && 
           ptr->type != tok_closebracket &&
           ptr->type != tok_empty)
            exp_tokens++;
    }
    
    ast->data = new_vector_mps_exp_node();
    vector_mps_exp_node_resize(&ast->data, exp_tokens);
    ast->root = mps_make_node(vec->ptr, vec->ptr + vec->size, ast);

    ast->depth = mps_get_depth(ast->root, 0);

    return 0;
}

void mps_delete_tree(mps_ast* tree) {
    vector_mps_exp_node_delete(&(tree->data));
    tree->root = NULL;
    tree->depth = 0;
}

