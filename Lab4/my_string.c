#include "my_string.h"

size_t my_strlen(const char* str, const char* delims)
{
    const char* p = str;
    size_t count = 0;

    if (str == NULL || str == '\0') {
        return 0;
    }

    while(*(p++) != *delims) {
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

    while(*p != '\0') {
        printf("*p: %c, *word: %c\n", *p, *word);
        if (*p == *word) {
            for (i = 0; i < word_size; i++) {
                if(*(word + i) == *(p + i)) {
                    same_char_count++;
                }
            }
            if (same_char_count == word_size) {
                index_of_word = p - str;
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
    char *p = str;

    while(*(p++) != '\0') {
        if (*p == ' ') {
            space_count++;
        }
    }

    p = str;

    for (i = 0; i < space_count; i++) {
        word_length = my_strlen(p, " ");
        for(j = 0; j < word_length / 2; j++) {
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
    static char* token;
    char* temp_token;
    static char* last_char_address;
    size_t delims_length;
    size_t i = 0;
    size_t word_length = 0;

    if (str_or_null != NULL) {
        token = str_or_null;
        last_char_address = token + my_strlen(str_or_null, "\0");
    } else {
        if (token == NULL) {
            return NULL;
        }
    }

    if (token == last_char_address - 1) {
        return NULL;
    }

    printf("token: %c\n", *token); 
    delims_length = my_strlen(delims, "\0");
    while (i < delims_length) {
        if (*token == delims[i]) {
            printf("token: %c, delims: %c\n", *token, delims[i]);
            token++;
            i = 0;
            continue;
        }
        i++;
    }
    temp_token = token;

    word_length = my_strlen(token, delims);
    for (i = 1; i < delims_length; ++i) {
        if (word_length > my_strlen(token, delims + i)) {
            word_length = my_strlen(token, delims + i);
        }
    }

    printf("token: %c, word_length: %zd\n", *token, word_length); 
    token += word_length;
    printf("token: %c\n", *token); 

    return temp_token;
}
