#include "translate.h"

int translate(int argc, const char** argv)
{
    char set1_buffer[512];
    char set2_buffer[512];
    char ch;
    size_t set1_size;
    size_t set2_size;
    size_t i;
    int is_printed = FALSE;
    error_code_t error_code = 0;

    if (strlen(argv[1]) > 511 || strlen(argv[2]) > 511) {
        error_code = ERROR_CODE_ARGUMENT_TOO_LONG;
        return error_code;
    }

    strncpy(set1_buffer, argv[1], 511);
    set1_buffer[511] = '\0';

    strncpy(set2_buffer, argv[2], 511);
    set2_buffer[511] = '\0';

    preprocess_basic(set1_buffer, set2_buffer);

    set1_size = strlen(set1_buffer);
    set2_size = strlen(set2_buffer);

    while (scanf("%c", &ch) == 1) {
        for (i = 0; i < set1_size; i++) {
            if (ch == set1_buffer[i]) {
                printf("%c", set2_buffer[i]);
                is_printed = TRUE;
            }
        }
        if (is_printed) {
            is_printed = FALSE;
            continue;
        }

        printf("%c", ch);
    }

    return error_code;
}

void preprocess_basic(char* set1_buffer, char* set2_buffer)
{
    size_t i = 0;
    size_t j = 1;
    size_t set1_size;
    size_t set2_size;

    set1_size = strlen(set1_buffer);
    set2_size = strlen(set2_buffer);

    if (set1_size > set2_size) {
        for (i = 0; i < set1_size - set2_size; i++) {
            set2_buffer[set2_size + i] = set2_buffer[set2_size - 1];
        }
    }

    while (set1_buffer[i] != '\0') {
        while(set1_buffer[j] != '\0') {
            if (set1_buffer[i] == set1_buffer[j]) {
                
            }
        }
    }
}