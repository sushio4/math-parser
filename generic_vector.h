#pragma once
#include <stdlib.h>
#include <stdbool.h>

//declares vector of TYPE with name vector_TYPE and defines functions for it
#define vector(TYPE) \
typedef struct vector_##TYPE {                          \
    TYPE* ptr;                                          \
    unsigned int size;                                  \
    unsigned int capacity;                              \
}vector_##TYPE;                                         \
                                                        \
vector_##TYPE new_vector_##TYPE () {                    \
    vector_##TYPE vec;                                  \
    vec.ptr = NULL;                                     \
    vec.size = vec.capacity = 0;                        \
    return vec;                                         \
}                                                       \
                                                        \
void resize(vector_##TYPE* vec, unsigned int size) {    \
    if(size <= vec->capacity) return;                   \
                                                        \
    TYPE* ptr = malloc(size * sizeof(TYPE));            \
    for(int i = 0; i < vec->size; i++)                  \
        ptr[i] = vec->ptr[i];                           \
                                                        \
    vec->capacity = size;                               \
    free(vec->ptr);                                     \
    vec->ptr = ptr;                                     \
}\
\
void push(vector_##TYPE* vec, TYPE e) {                 \
    if(vec->size == vec->capacity) {                    \
        if(vec->size == 0) resize(vec, 2);              \
        else resize(vec, vec->size*2);                  \
    }                                                   \
                                                        \
    vec->ptr[vec->size++] = e;                          \
}\
\
TYPE pop(vector_##TYPE* vec) {                          \
    return vec->ptr[--vec->size];                       \
}\
\
bool at(vector_##TYPE* vec, unsigned int index, TYPE* dest) {\
    if(index >= vec->size) return false;                \
    *dest = vec->ptr[index];                            \
    return true;                                        \
}
