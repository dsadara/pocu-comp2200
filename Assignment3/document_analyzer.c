#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "document_analyzer.h"


char* g_document_buffer = NULL;
char** g_sentence_buffer = NULL;
char** g_paragraph_buffer = NULL;
char*** g_sentence_buffer_addresses = NULL;
char* g_word = NULL;
/*char*** g_sentence = NULL; */
const char**** g_paragraph;
char***** g_docuemnt = NULL;
size_t** g_paragraph_to_sentence_to_word = NULL;
size_t* g_sentence_word_num = NULL; 
size_t* g_paragraph_to_sentence_num = NULL;
size_t g_buffer_size = 0;
size_t g_sentence_num = 0;
size_t g_paragraph_num = 0;


int load_document(const char* document)
{
    size_t j;
    size_t i;
    size_t k;
    size_t word_num;
    const char delims1[] = ".!?";
    const char delims2[] = " ,";
    const char delims3[] = "\n";
    
    FILE* stream;
    stream = fopen(document, "rb");
    if (stream == NULL) {
        fprintf(stderr, "error while opening %s\n", document);
        return FALSE;
    }

    while (fgetc(stream) != EOF) {
        g_buffer_size++;
    }
    rewind(stream);
    g_document_buffer = malloc(g_buffer_size + 1);                                          
    fread(g_document_buffer, sizeof(char), g_buffer_size, stream);
    g_document_buffer[g_buffer_size] = '\0';
    
    g_paragraph_num = get_buffer_paragraph_count();
    g_paragraph_to_sentence_to_word = malloc(sizeof(size_t*) * g_paragraph_num);            
    g_paragraph_to_sentence_num = malloc(sizeof(size_t) * g_paragraph_num);                 
    g_paragraph_buffer = malloc(sizeof(char*) * g_paragraph_num);                           
    g_paragraph_buffer[0] = strtok(g_document_buffer, delims3);
    for (i = 1; i < g_paragraph_num; i++) {
        g_paragraph_buffer[i] = strtok(NULL, delims3);
    }

    g_paragraph = malloc(sizeof(char***) * g_paragraph_num);    
    g_sentence_buffer_addresses = malloc(sizeof(char**) * g_paragraph_num);                                             
    for (i = 0; i < g_paragraph_num; i++) {
        const char*** g_sentences_tmp;

        g_sentence_num = get_sentence_count(g_paragraph_buffer[i]);
        g_paragraph_to_sentence_num[i] = g_sentence_num;
        g_sentence_word_num = malloc(sizeof(size_t) * g_sentence_num);                     
        g_sentence_buffer = malloc(sizeof(char*) * g_sentence_num);                         
        g_sentence_buffer_addresses[i] = g_sentence_buffer;
        g_sentence_buffer[0] = strtok(g_paragraph_buffer[i], delims1);
        for (j = 1; j < g_sentence_num; j++) {
            g_sentence_buffer[j] = strtok(NULL, delims1);
        }

        g_sentences_tmp = malloc(sizeof(char**) * g_sentence_num);                          
        for (j = 0; j < g_sentence_num; j++) {
            const char** g_words_tmp;

            word_num = get_word_count(g_sentence_buffer[j]);
            g_sentence_word_num[j] = word_num;
            g_words_tmp = malloc(sizeof(char*) * word_num);                                 
            g_words_tmp[0] = strtok(g_sentence_buffer[j], delims2);
            for (k = 1; k < word_num; k++) {
                g_words_tmp[k] = strtok(NULL, delims2);
            }
            g_sentences_tmp[j] = g_words_tmp;
        }
        g_paragraph[i] = g_sentences_tmp;
        g_paragraph_to_sentence_to_word[i] = g_sentence_word_num;
    }

    /*
        for (i = 0; i < g_paragraph_num; i++) {
            printf("**paragraph[%d]**\n", i);
            for (j = 0; j < g_paragraph_to_sentence_num[i]; j++) {
                for (k = 0; k < g_paragraph_to_sentence_to_word[i][j]; k++) {
                    printf("%s\n", g_paragraph[i][j][k]);
                }
            }
        }
    */

    /*
    g_sentence_num = get_total_sentence_count();
    g_sentence_buffer = malloc(sizeof(char*) * g_sentence_num);
    g_sentence_buffer[0] = strtok(g_document_buffer, delims1);
    for (i = 1; i < g_sentence_num; i++) {
        g_sentence_buffer[i] = strtok(NULL, delims1);
    }

    g_sentence = malloc(sizeof(char**) * g_sentence_num);
    for (i = 0; i < g_sentence_num; i++) {
        word_num = get_word_count(g_sentence_buffer[i]);
        word_num_array[i] = word_num;
        g_words_tmp = malloc(sizeof(char**) * word_num);
        g_words_tmp[0] = strtok(g_sentence_buffer[i], delims2);
        for (j = 1; j < word_num; j++) {
            g_words_tmp[j] = strtok(NULL, delims2);
        }
        g_sentence[i] = g_words_tmp;
    }

    
    for (i = 0; i < g_sentence_num; i++) {
        for (j = 0; j < word_num_array[i]; j++) {
            printf("sentence[%d][%d]%s\n", i, j, g_sentence[i][j]);
        }
    }
    */
    if (fclose(stream) != 0) {
        fprintf(stderr, "error while closing\n");
    }

    return TRUE;
}

void dispose(void)
{
    size_t i;
    size_t j;

    free(g_document_buffer);
    free(g_paragraph_buffer);
    for (i = 0; i < g_paragraph_num; i++) {
            for (j = 0; j < g_paragraph_to_sentence_num[i]; j++) {
                free(g_paragraph[i][j]);
        }
    }
    for (i = 0; i < g_paragraph_num; i++) {
        free(g_paragraph[i]);
    }
    free(g_paragraph);
    for (i = 0; i < g_paragraph_num; i++) {
        free(g_sentence_buffer_addresses[i]);
    }
    free(g_sentence_buffer_addresses);
    for (i= 0; i < g_paragraph_num; i++) {
        free(g_paragraph_to_sentence_to_word[i]);
    }
    free(g_paragraph_to_sentence_to_word);
    free(g_paragraph_to_sentence_num);
}

size_t get_total_word_count(void)
{
    size_t i;
    size_t count = 0;

    for (i = 0; i < g_paragraph_num; i++) {
        count += get_paragraph_word_count(g_paragraph[i]);
    }

    return count;
}

size_t get_total_sentence_count(void)
{
    size_t i;
    size_t count = 0;
    for (i = 0; i < g_paragraph_num; i++) {
        count += get_paragraph_sentence_count(g_paragraph[i]);
    }

    return count;
}

size_t get_total_paragraph_count(void)
{
    return g_paragraph_num;
}
/*
size_t get_total_word_count(void)
{
    size_t i;
    size_t count = 0;
    for (i = 0; i < g_buffer_size; i++) {
        if (g_document_buffer[i] == ' ') {
            count++;
        }

        if (g_document_buffer[i] == ',' && g_document_buffer[i + 1] == ' ' ) {
            i++;
            count++;
        }

        if ((g_document_buffer[i] == '.' || g_document_buffer[i] == '!' || g_document_buffer[i] == '?') && g_document_buffer[i + 1] == ' ' ) {
            i++;
            count++;
        }

        if ((g_document_buffer[i] == '.' || g_document_buffer[i] == '!' || g_document_buffer[i] == '?') && g_document_buffer[i + 1] == '\n' ) {
            i++;
            count++;
        }

        if (g_document_buffer[i] == '.' || g_document_buffer[i] == '!' || g_document_buffer[i] == '?') {
            count++;
        }
    }
    return count;
}

size_t get_total_sentence_count(void)
{
    size_t i;
    size_t count = 0;
    for (i = 0; i < g_buffer_size; i++) {
        if (g_document_buffer[i] == '.' || g_document_buffer[i] == '!' || g_document_buffer[i] == '?') {
            count++;
        }
    }
    return count;
}

size_t get_total_paragraph_count(void)
{
    size_t i;
    size_t count = 1;
    for (i = 0; i < g_buffer_size; i++) {
        if ((g_document_buffer[i] == '.' || g_document_buffer[i] == '!' || g_document_buffer[i] == '?') && g_document_buffer[i + 1] == '\n') {
            i++;
            count++;
        }
    }
    return count;
}
*/
const char*** get_paragraph_or_null(const size_t paragraph_index)
{
    if (paragraph_index > g_paragraph_num - 1 || g_paragraph == NULL) {
        return NULL;
    }
    return g_paragraph[paragraph_index];
}

size_t get_paragraph_word_count(const char*** paragraph)
{
    size_t i;
    size_t paragraph_index;
    size_t word_count = 0;

    for (i = 0; i < g_paragraph_num; i++) {
        if (g_paragraph[i] == paragraph) {
            paragraph_index = i;
        }
    }

    for (i = 0; i < g_paragraph_to_sentence_num[paragraph_index]; i++) {
        word_count += g_paragraph_to_sentence_to_word[paragraph_index][i];
    }

    return word_count;
}

size_t get_paragraph_sentence_count(const char*** paragraph)
{
    size_t i;
    size_t paragraph_index;

    for (i = 0; i < g_paragraph_num; i++) {
        if (g_paragraph[i] == paragraph) {
            paragraph_index = i;
        }
    }

    return g_paragraph_to_sentence_num[paragraph_index];
}

const char** get_sentence_or_null(const size_t paragraph_index, const size_t sentence_index)
{
    if (paragraph_index > g_paragraph_num - 1 || sentence_index > g_paragraph_to_sentence_num[paragraph_index] - 1) {
        return NULL;
    }
    if (g_paragraph == NULL) {
        return NULL;
    }
    return g_paragraph[paragraph_index][sentence_index];
}

size_t get_sentence_word_count(const char** sentence)
{
    size_t i;
    size_t j;
    size_t paragraph_index;
    size_t sentence_index;

    for (i = 0; i < g_paragraph_num; i++) {
        for (j = 0; j < g_sentence_num; j++) {
            if (g_paragraph[i][j] == sentence) {
                paragraph_index = i;
                sentence_index = j;
            }
        }
    }

    return g_paragraph_to_sentence_to_word[paragraph_index][sentence_index];
}

int print_as_tree(const char* filename)
{
    size_t i;
    size_t j;
    size_t k;
    FILE* stream;
    stream = fopen(filename, "wb");
    if (stream == NULL) {
        fprintf(stderr, "error while opening %s\n", filename);
        return FALSE;
    }

    for (i = 0; i < g_paragraph_num; i++) {
        fprintf(stream, "Paragraph %zd:\n", i);
        for (j = 0; j < g_paragraph_to_sentence_num[i]; j++) {
            fprintf(stream, "    Sentence %zd:\n", j);
            for (k = 0; k < g_paragraph_to_sentence_to_word[i][j]; k++) {
                fprintf(stream, "        %s\n", g_paragraph[i][j][k]);
            }
        }
        fprintf(stream, "\n");
    }

    if (fclose(stream) != 0) {
        fprintf(stderr, "error while closing\n");
    }

    return TRUE;
}


size_t get_word_count(char* sentence)
{
    size_t count = 1;
    char* s = sentence;

    if (*s == ' ') {
        count--;
    }

    while (*s != '\0') {
        if (*s == ' ') {
            count++;
        }
        s++;
    }

    return count;
}

size_t get_sentence_count(char* paragraph)
{
    size_t count = 0;
    char* p = paragraph;

    while  (*p != '\0') {
        if (*p == '.' || *p == '!' || *p == '?') {
            count++;
        }
        p++;
    }

    return count;
}

size_t get_buffer_paragraph_count(void)
{
    size_t i;
    size_t count = 1;
    for (i = 0; i < g_buffer_size; i++) {
        if ((g_document_buffer[i] == '.' || g_document_buffer[i] == '!' || g_document_buffer[i] == '?') && g_document_buffer[i + 1] == '\n') {
            i++;
            count++;
        }
    }
    return count;
}