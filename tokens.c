#include "tokens.h"
#include <stdlib.h>

static const char* mps_operators = "+-*/^";

define_vector(mps_token)

mps_token mps_make_token(const char* str, unsigned char candidates) {
    if(!candidates) candidates = ALL_MASK;

    mps_token token = empty_token;

    int length = strlen(str);
    if(length == 0) return token;
    if(length > MAX_TOKEN_STR_SIZE) return token;

    //check for operators and interpunction 
    if(length == 1) {
        char* pos = strchr(mps_operators, str[0]);
        if(pos != NULL) {
            token.type = tok_operation;
            token.op = *pos;

            return token;
        } 

        switch(*str){
            case '(':
                token.type = tok_openbracket;
                break;
            case ')':
                token.type = tok_closebracket;
                break;
            case ',':
                token.type = tok_comma;
                break;
        }

        if(token.type != tok_empty)
            return token;
    }

    //check for functions
    for(int i = 0; i < mps_func_num; i++) 
        if(strcmp(str, mps_func_names[i]) == 0) {
            token.type = tok_function;
            token.func = (mps_functions)i;
            return token;
        }

    //check for number
    {
        char* endp;
        double val = strtod(str, &endp);
        if(endp != str) {
            token.type = tok_constant;
            token.val = val;
            return token;
        }
    }

    //if none of the above then probably a variable
    token.type = tok_variable;
    strcpy(token.var_name, str);
    return token;
}

int mps_tokenize(const char* str, vector_mps_token* token_vector) {
    if(!token_vector) return 0;

    //denotes start of currently checked token
    const char* tok_start_ptr = str;
    //masks which token type could it be
    unsigned char candidates = ALL_MASK;
    int tok_count = 0;

    char token_str[MAX_TOKEN_STR_SIZE + 1] = "";

    for(const char* ptr = str; *ptr; ptr++) {
        //checking first character of the token
        if(ptr == tok_start_ptr) {
            //operator/interpunction found
            if(strchr(mps_operators, *ptr) || strchr(",()", *ptr)) {
                strncpy(token_str, ptr, 1);
                mps_token token = mps_make_token(token_str, 0);
                vector_mps_token_push(token_vector, token);
                tok_count++;
                tok_start_ptr++;
                continue;
            }

            if(strchr(" \n\0", *ptr) != NULL) {
                tok_start_ptr++;
                continue;
            }

            //letter
            if((*ptr >= 'a' && *ptr <= 'z') || (*ptr >= 'A' && *ptr <= 'Z') || *ptr == '_') {
                candidates = VAR_MASK + FUNC_MASK;
            }

            else if(*ptr >= '0' && *ptr <= '9') {
                candidates = CONST_MASK;
            }
        }

        //if the next character does not fit constant token type
        if(candidates == CONST_MASK && !(
            (*(ptr+1) >= '0' && *(ptr+1) <= '9') || strchr(" .'", *(ptr+1))
        )) {
            if(ptr - tok_start_ptr > MAX_TOKEN_STR_SIZE) return 0;

            goto make_token;
        }

        //if it does not fit variable/function token type
        if(candidates == VAR_MASK + FUNC_MASK && !(
            ((*(ptr+1) >= 'a' && *(ptr+1) <= 'z') || (*(ptr+1) >= 'A' && *(ptr+1) <= 'Z') || *(ptr+1) == '_') ||
            (*(ptr+1) >= '0' && *(ptr+1) <= '9')
        )) {
            if(ptr - tok_start_ptr > MAX_TOKEN_STR_SIZE) return 0;

            goto make_token;
        }

        if(strchr(" \n\0", *(ptr+1)) != NULL) {
            if(ptr - tok_start_ptr > MAX_TOKEN_STR_SIZE) return 0;

            goto make_token;
        }

        continue;

    make_token:
        strncpy(token_str, tok_start_ptr, (ptr+1 - tok_start_ptr));
        mps_token token = mps_make_token(token_str, candidates);
        vector_mps_token_push(token_vector, token);
        tok_start_ptr = ptr + 1;
        tok_count++;
        candidates = ALL_MASK;
        memset(token_str, '\0', MAX_TOKEN_STR_SIZE);
    }

    return tok_count;
}