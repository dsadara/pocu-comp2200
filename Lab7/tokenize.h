#ifndef TOKENIZE_H
#define TOKENIZE_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define _CRT_SECURE_NO_WARNINGS
#define LINE_LENGTH (2048)

char** tokenize_malloc(const char* str, const char* delim);

size_t trim_string(char* str, size_t str_length);

#endif /* TOKENIZE_H */
