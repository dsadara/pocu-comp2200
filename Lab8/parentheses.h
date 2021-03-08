#ifndef PARENTHESES_H
#define PARENTHESES_H

#include <stdlib.h>

typedef struct {
    size_t opening_index;
    size_t closing_index;
} parenthesis_t;

typedef struct {
    char parentheses;
    size_t stack_element_count;
} parentheses_and_index_t;

size_t get_matching_parentheses(parenthesis_t* parentheses, size_t max_size, const char* str);

int find_stack_element(parentheses_and_index_t* my_stack, size_t stack_element_count, char element);

int comp(const void* a, const void* b);

#endif /* PARENTHESES_H */
