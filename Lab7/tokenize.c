#include "tokenize.h"

char** tokenize_malloc(const char* str, const char* delim)
{
    size_t i;
    size_t j;
    size_t str_length;
    size_t delim_num;
    size_t token_num;
    size_t line_length;
    char* buffer;
    char* b;
    char** lines;
    const char* d;
    const char* s;

    if (str[0] == '\0') {
        return NULL;
    }

    printf("str: %c, %d, %p", *str, *str, (void*)str);

    d = delim;
    s = str;
    line_length = 1024;

    str_length = strlen(str);
    while (str_length >= line_length) {
        line_length *= 2;
    }
    buffer = malloc(line_length);
    strcpy(buffer, str);

    delim_num = strlen(delim);

    for (i = 0; i < str_length; i++) {
        for (j = 0; j < delim_num; j++) {
            if (d[j] == s[i]) {
                buffer[i] = '\0';
            }
        }
    }

    str_length = trim_string(buffer, str_length);
    token_num = 1;
    b = buffer;
    
    for (i = 0; i < str_length;) {
        if (b[i] == '\0') {
            token_num++;
            while (b[i] == '\0') {
                i++;
            }
            continue;
        }
        i++;
    }

    lines = malloc(sizeof(char*) * (token_num + 1));
    for (i = 0; i < token_num; i++) {
        lines[i] = malloc(strlen(b) + 1);
        strcpy(lines[i], b);
        while (*b != '\0') {
            b++;
        }
        while (*b == '\0') {
            b++;
        }
    }
    lines[token_num] = NULL;
    
    free(buffer);
    
    return lines;
}

size_t trim_string(char* str, size_t str_length)
{
    size_t i;
    size_t j;
    size_t left_nullchar_count;
    size_t right_nullchar_count;
    char* s;

    left_nullchar_count = 0;
    right_nullchar_count = 0;
    s = str;

    while (*s++ == '\0') {
        left_nullchar_count++;
    }

    s = (str + str_length) - 1;

    while (*s-- == '\0') {
        right_nullchar_count++;
    }

    for (i = 0; i < left_nullchar_count; i++) {
        for (j = 0; j < str_length; j++) {
            str[j] = str[j + 1];
        }
        str_length--;
    }

    return str_length - right_nullchar_count;
}
