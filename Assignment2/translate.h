#ifndef TRANSLATE_H
#define TRANSLATE_H

#include <stdio.h>
#include <string.h>

#define TRUE (1)
#define FALSE (0)

typedef enum error_code {
    ERROR_CODE_WRONG_ARGUMENTS_NUMBER = 1,
    ERROR_CODE_INVALID_FLAG,
    ERROR_CODE_INVALID_FORMAT,
    ERROR_CODE_ARGUMENT_TOO_LONG,
    ERROR_CODE_INVALID_RANGE
} error_code_t;

int translate(int argc, const char** argv);

void preprocess_basic(char* set1_buffer, char* set2_buffer);

void delete_char(char* set_buffer, size_t index, size_t set_size);

int preprocess_escape(char* set_buffer);

int preprocess_scope(char* set_buffer);

void add_char(char* set_buffer, size_t set_size, char ch, const size_t pos);

#endif /* TRANSLATE_H */
