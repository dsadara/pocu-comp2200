#include "translate.h"

int translate(int argc, const char** argv)
{
    char set1_buffer[512];
    char set2_buffer[512];
    char ch;
    size_t set1_size;
    size_t set2_size;
    size_t i;
    size_t set1_index = 1;
    size_t set2_index = 2;
    int is_printed = FALSE;
    int is_case_ignored = FALSE;
    error_code_t error_code = 0;

    if (argc == 4) {
        set1_index = 2;
        set2_index = 3;
        is_case_ignored = TRUE;
    }

    if (strlen(argv[set1_index]) > 511 || strlen(argv[set2_index]) > 511) {
        error_code = ERROR_CODE_ARGUMENT_TOO_LONG;
        return error_code;
    }

    strncpy(set1_buffer, argv[set1_index], 511);
    set1_buffer[511] = '\0';

    strncpy(set2_buffer, argv[set2_index], 511);
    set2_buffer[511] = '\0';

    error_code = preprocess_escape(set1_buffer);
    error_code = preprocess_scope(set1_buffer);
    preprocess_basic(set1_buffer, set2_buffer);

    set1_size = strlen(set1_buffer);
    set2_size = strlen(set2_buffer);

    while (scanf("%c", &ch) == 1) {
        for (i = 0; i < set1_size; i++) {
            if (ch == set1_buffer[i]) {
                printf("%c", set2_buffer[i]);
                is_printed = TRUE;
            }
            if (is_case_ignored && (ch + 32) == set1_buffer[i]) {
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
    size_t i;
    size_t j;
    size_t set1_size;
    size_t set2_size;
    char ch;

    set1_size = strlen(set1_buffer);
    set2_size = strlen(set2_buffer);

    if (set1_size < set2_size) {
        set2_buffer[set1_size] = '\0';
    }

    if (set1_size > set2_size) {
        for (i = 0; i < set1_size - set2_size; i++) {
            set2_buffer[set2_size + i] = set2_buffer[set2_size - 1];
        }
    }

    for (i = 0; set1_buffer[i] != '\0'; i++) {
        ch = set1_buffer[set1_size - 1 - i];
        for (j = i + 1; set1_buffer[j] != '\0'; j++) {
            if (set1_buffer[set1_size - 1 - j] == ch) {
                delete_char(set1_buffer, set1_size - 1 - j, set1_size);
                delete_char(set2_buffer, set1_size - 1 - j, set2_size);
                set1_size--;
                set2_size--;
                j--;
                i--;
            }
        }
    }
}

void delete_char(char* set_buffer, size_t index, size_t set_size) 
{
    size_t i;
    
    for (i = index; i < set_size; i++) {
        set_buffer[i] = set_buffer[i + 1];
    }
}

int preprocess_escape(char* set_buffer)
{
    size_t i;
    size_t set_size;
    error_code_t error_code = 0;

    set_size = strlen(set_buffer);

    for (i = 0; set_buffer[i] != '\0'; i++) {
        if (set_buffer[i] == 92) {

            switch (set_buffer[i + 1]) {
            case 'a':
                set_buffer[i] = '\a';
                delete_char(set_buffer, i + 1, set_size);
                break;
            case 'b':
                set_buffer[i] = '\b';
                delete_char(set_buffer, i + 1, set_size);
                break;
            case 't':
                set_buffer[i] = '\t';
                delete_char(set_buffer, i + 1, set_size);
                break;
            case 'n':
                set_buffer[i] = '\n';
                delete_char(set_buffer, i + 1, set_size);
                break;
            case 'v':
                set_buffer[i] = '\v';
                delete_char(set_buffer, i + 1, set_size);
                break;
            case 'f':
                set_buffer[i] = '\f';
                delete_char(set_buffer, i + 1, set_size);
                break;
            case 'r':
                set_buffer[i] = '\r';
                delete_char(set_buffer, i + 1, set_size);
                break;
            case 34:
                set_buffer[i] = 34;
                delete_char(set_buffer, i + 1, set_size);
                break;
            case 39:
                set_buffer[i] = 39;
                delete_char(set_buffer, i + 1, set_size);
                break;
            case 92:
                set_buffer[i] = 92;
                delete_char(set_buffer, i + 1, set_size);
                break;
            default:
                error_code = ERROR_CODE_INVALID_FORMAT;
                break;
            }
        }
    }
    return error_code;
}

int preprocess_scope(char* set_buffer)
{
    size_t i;
    size_t j;
    size_t set_size;
    char start_char;
    char end_char;
    error_code_t error_code = 0;
    int is_next_specifier_not_valid = FALSE;
    set_size = strlen(set_buffer);
    /*
    for (i = 0; set_buffer[i] != '\0'; i++) {
        if (set_buffer[i] == '-' && set_buffer[i + 2] == '-') {
            delete_char(set_buffer, i + 2, set_size);
            set_size--;
        }
        if (set_buffer[i] == '-' && set_buffer[i + 1] == '-') {
            delete_char(set_buffer, i + 1, set_size);
            set_size--;
        }
    }
    */
    for (i = 0; set_buffer[i] != '\0'; i++) {
        if (set_buffer[i] == '-') {
            if (i == 0 || i == set_size - 1) {
                continue;
            }
            if (is_next_specifier_not_valid) {
                is_next_specifier_not_valid = FALSE;
                continue;
            }
            if (set_buffer[i + 2] == '-') {
                is_next_specifier_not_valid = TRUE;
            }
            delete_char(set_buffer, i, set_size);
            set_size--;
            i--; 
            start_char = set_buffer[i];
            end_char = set_buffer[i + 1];
            if (start_char > end_char) {
                error_code = ERROR_CODE_INVALID_RANGE;
                return error_code;
            } else if (start_char == end_char) {
                delete_char(set_buffer, i, set_size);
                set_size--;
            }
            for (j = start_char + 1; j < (size_t)end_char; j++) {
                add_char(set_buffer, set_size, j, i + 1);
                set_size++;
                i++;
            }
        }
    }
    return error_code;
}

void add_char(char* set_buffer, size_t set_size, char ch, const size_t pos)
{
    size_t i;

    for (i = set_size; i > pos; i--) {
        set_buffer[i] = set_buffer[i - 1];
    }
    set_buffer[pos] = ch;
}
