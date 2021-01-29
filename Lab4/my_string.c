#include "my_string.h"

size_t my_strlen(const char* str, const char* delims)
{
    const char* p = str;
    size_t count = 0;

    if (str == NULL || *str == '\0') {
        return 0;
    }

    while (*(p++) != *delims) {
        count++;
    }
    return count;
}

void reverse(char* str)
{
    size_t length = my_strlen(str, "\0");
    size_t i;
    char temp;

    for (i = 0; i < length / 2; i++) {
        temp = str[i];
        str[i] = str[length - 1 - i];
        str[length - 1 - i] = temp;
    }
}

int index_of(const char* str, const char* word)
{
    size_t i;
    size_t same_char_count = 0;
    size_t word_size = my_strlen(word, "\0");
    const char* p = str;
    int index_of_word = -1;

    if (word == NULL) {
        return -1;
    }

    while (*p != '\0') {
        if (*p == *word) {
            for (i = 0; i < word_size; i++) {
                if (*(word + i) == *(p + i)) {
                    same_char_count++;
                }
            }
            if (same_char_count == word_size) {
                index_of_word = p - str;
                return index_of_word;
            }
            same_char_count = 0;
        }
        p++;
    }

    return index_of_word;
}

void reverse_by_words(char* str)
{
    size_t space_count = 0;
    size_t i;
    size_t j;
    size_t word_length;
    char temp;
    char* p = str;

    while (*(p++) != '\0') {
        if (*p == ' ') {
            space_count++;
        }
    }

    p = str;

    for (i = 0; i < space_count; i++) {
        word_length = my_strlen(p, " ");
        for (j = 0; j < word_length / 2; j++) {
            temp = p[j];
            p[j] = p[word_length - 1 - j];
            p[word_length - 1 - j] = temp;
        }
        p += word_length + 1;
    }

    reverse(p);
}

char* tokenize(char* str_or_null, const char* delims)
{
    static size_t s_str_length;
    static char* s_token;
    char* token_returning;
    size_t i;
    size_t j;
    
    if (str_or_null != NULL) {
        size_t delims_length;
        s_token = str_or_null;
        delims_length = my_strlen(delims, "\0");
        s_str_length = my_strlen(s_token, "\0");
        for (i = 0; i < delims_length; i++) {
            for (j = 0; j < s_str_length; j++) {
                if (s_token[j] == delims[i]) {
                    s_token[j] = 0;
                }
            }
        }
    }

    if (s_token == NULL) {
        return NULL;
    }

    while (*s_token == '\0') {
        s_token++;
    }
    token_returning = s_token;
    
    while (*s_token != '\0') {
        s_token++;
    }

    return token_returning;
}

char* reverse_tokenize(char* str_or_null, const char* delims)
{
    char* token;

    token = tokenize(str_or_null, delims);
    reverse(token);

    return token;
}
