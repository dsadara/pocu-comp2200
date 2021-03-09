#include "parentheses.h"

int comp(const void* a, const void* b)  
{
    size_t num1 = ((parenthesis_t*)a)->opening_index;    
    size_t num2 = ((parenthesis_t*)b)->opening_index;   

    if (num1 < num2) {
        return -1;
    }     
    
    if (num1 > num2) {
        return 1;
    } 

    return 0;   
}

size_t get_matching_parentheses(parenthesis_t* parentheses, size_t max_size, const char* str)
{
    const char* s = str;
    parentheses_and_index_t* my_stack;
    size_t stack_element_count = 0;
    size_t parenthesis_array_index = 0;
    size_t i;
    int find_result;

    my_stack = malloc(sizeof(parentheses_and_index_t) * max_size);

    while (*s != '\0') {

        if (*s == '{' || *s == '(' || *s == '[' || *s == '<') {
            if (stack_element_count >= max_size) {
                s++;
                continue;
            }
            printf("parenthesis %c in!! index:%d\n", *s, s - str);
            my_stack[stack_element_count].parentheses = *s;
            my_stack[stack_element_count++].stack_element_count = s - str;
        }
        /*
        if (parenthesis_array_index >= max_size) {
            s++;
            continue;
        }
        */
        if (*s == '}') {
            printf("find %c..pair index:%d\n", *s, s - str);
            find_result = find_stack_element(my_stack, stack_element_count, '{');
            if (find_result != -1) {
                parentheses[parenthesis_array_index].opening_index = my_stack[find_result].stack_element_count;
                for (i = find_result; i < stack_element_count; i++) {
                    my_stack[i] = my_stack[i + 1];
                }
                stack_element_count--;
                parentheses[parenthesis_array_index++].closing_index = s - str;
            }
        }
        if (*s == ')') {
            printf("find %c's pair.. index:%d\n", *s, s - str);
            find_result = find_stack_element(my_stack, stack_element_count, '(');
            if (find_result != -1) {
                parentheses[parenthesis_array_index].opening_index = my_stack[find_result].stack_element_count;
                for (i = find_result; i < stack_element_count; i++) {
                    my_stack[i] = my_stack[i + 1];
                }
                stack_element_count--;
                parentheses[parenthesis_array_index++].closing_index = s - str;
            }
        }
        if (*s == ']') {
            printf("find %c..pair index:%d\n", *s, s - str);
            find_result = find_stack_element(my_stack, stack_element_count, '[');
            if (find_result != -1) {
                parentheses[parenthesis_array_index].opening_index = my_stack[find_result].stack_element_count;
                for (i = find_result; i < stack_element_count; i++) {
                    my_stack[i] = my_stack[i + 1];
                }
                stack_element_count--;
                parentheses[parenthesis_array_index++].closing_index = s - str;
            }
        }
        if (*s == '>') {
            printf("find %c..pair index:%d\n", *s, s - str);
            find_result = find_stack_element(my_stack, stack_element_count, '<');
            if (find_result != -1) {
                parentheses[parenthesis_array_index].opening_index = my_stack[find_result].stack_element_count;
                for (i = find_result; i < stack_element_count; i++) {
                    my_stack[i] = my_stack[i + 1];
                }
                stack_element_count--;
                parentheses[parenthesis_array_index++].closing_index = s - str;
            }
        }
        s++;
    }

   

    free(my_stack);
    printf("parenthesis_array_index:%d\n", parenthesis_array_index);
    qsort(parentheses, parenthesis_array_index, sizeof(parenthesis_t), comp);

    if (parenthesis_array_index >= max_size) {
        parenthesis_array_index = max_size;
    }

    return parenthesis_array_index;
}


int find_stack_element(parentheses_and_index_t* my_stack, size_t stack_element_count, char element)
{
    char popped_element;
    int is_element_founded = 0;

    if (stack_element_count == 0) {
        return -1;
    }

    do {
        popped_element = my_stack[--stack_element_count].parentheses;
        if (popped_element == element) {
            is_element_founded = 1;
            break;
        }
    } while (stack_element_count != 0);
    
    if (!is_element_founded) {
        return -1;
    }

    return stack_element_count;
}
