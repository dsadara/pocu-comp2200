#ifndef TOKENIZE_H
#define TOKENIZE_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char** tokenize_malloc(const char* str, const char* delim);

size_t trim_string(char* str, size_t str_length);

#endif /* TOKENIZE_H */
