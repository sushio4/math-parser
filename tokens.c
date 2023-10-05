#include "tokens.h"
#include <stdlib.h>

static const char* mps_operators = "+-*/^";

mps_token mps_make_token(const char* str) {
    mps_token token = empty_token;

    int length = strlen(str);
    if(length == 0) return token;
    if(length > MAX_TOKEN_STR_SIZE) return token;

    //check for operators and interpunction 
    if(length == 1) {
        char* pos = strchr(mps_operators, str[0]);
        if(pos != NULL) {
            token.type = operation;
            token.op = *pos;

            return token;
        } 

        switch(*str){
            case '(':
                token.type = openbracket;
                break;
            case ')':
                token.type = closebracket;
                break;
            case ',':
                token.type = comma;
                break;
        }

        if(token.type != empty)
            return token;
    }

    //check for functions
    for(int i = 0; i < mps_func_num; i++) 
        if(strcmp(str, mps_func_names[i]) == 0) {
            token.type = function;
            token.func = (mps_functions)i;
            return token;
        }

    //check for number
    {
        char* endp;
        double val = strtod(str, &endp);
        if(endp != str) {
            token.type = constant;
            token.val = val;
            return token;
        }
    }

    //if none of the above then probably a variable
    token.type = variable;
    strcpy(token.var_name, str);
    return token;
}

