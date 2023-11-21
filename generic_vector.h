#pragma once
#include <stdlib.h>
#include <stdbool.h>

//only declares vector and functions
#define declare_vector(TYPE) \
typedef struct vector_##TYPE {                          \
    TYPE* ptr;                                          \
    unsigned int size;                                  \
    unsigned int capacity;                              \
}vector_##TYPE;                                         \
                                                        \
vector_##TYPE new_vector_##TYPE (); \
void vector_##TYPE##_resize(vector_##TYPE* vec, unsigned int size); \
void vector_##TYPE##_push(vector_##TYPE* vec, TYPE e); \
TYPE vector_##TYPE##_pop(vector_##TYPE* vec); \
bool vector_##TYPE##_at(vector_##TYPE* vec, unsigned int index, TYPE* dest); \
void vector_##TYPE##_delete(vector_##TYPE* vec);

//defines functions for vector_TYPE
#define define_vector(TYPE) \
                                                        \
vector_##TYPE new_vector_##TYPE () {                    \
    vector_##TYPE vec;                                  \
    vec.ptr = NULL;                                     \
    vec.size = vec.capacity = 0;                        \
    return vec;                                         \
}                                                       \
                                                        \
void vector_##TYPE##_resize(vector_##TYPE* vec, unsigned int size) {    \
    if(size <= vec->capacity) return;                   \
                                                        \
    TYPE* ptr = (TYPE*)malloc(size * sizeof(TYPE));            \
    for(int i = 0; i < vec->size; i++)                  \
        ptr[i] = vec->ptr[i];                           \
                                                        \
    vec->capacity = size;                               \
    free(vec->ptr);                                     \
    vec->ptr = ptr;                                     \
}\
\
void vector_##TYPE##_push(vector_##TYPE* vec, TYPE e) {                 \
    if(vec->size == vec->capacity) {                    \
        if(vec->size == 0) vector_##TYPE##_resize(vec, 2);              \
        else vector_##TYPE##_resize(vec, vec->size*2);                  \
    }                                                   \
                                                        \
    vec->ptr[vec->size++] = e;                          \
}\
\
TYPE vector_##TYPE##_pop(vector_##TYPE* vec) {                          \
    return vec->ptr[--vec->size];                       \
}\
\
bool vector_##TYPE##_at(vector_##TYPE* vec, unsigned int index, TYPE* dest) {\
    if(index >= vec->size) return false;                \
    *dest = vec->ptr[index];                            \
    return true;                                        \
}\
\
void vector_##TYPE##_delete(vector_##TYPE* vec) { \
    free(vec->ptr);                                     \
    vec->size = vec->capacity = 0;                      \
}
