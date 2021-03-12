#include <stdlib.h>
#include <stdio.h>
#include "document_analyzer.h"

char* g_document_buffer = NULL;
char* g_word = NULL;
char** g_sentence = NULL;
char*** g_paragraph = NULL;
char**** g_docuemnt = NULL;
size_t g_buffer_size = 0;


int load_document(const char* document)
{
    size_t word_num;
    size_t sentence_num;
    size_t paragraph_num;
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
    g_document_buffer = malloc(g_buffer_size);
    fread(g_document_buffer, sizeof(char), g_buffer_size, stream);

    word_num = get_total_word_count();
    g_word = malloc(word_num)

    if (fclose(stream) != 0) {
        fprintf(stderr, "error while closing\n");
    }


    return TRUE;
}

void dispose(void)
{
    free(g_document_buffer);
}

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
/*
const char*** get_paragraph_or_null(const size_t paragraph_index)
{

}

size_t get_paragraph_word_count(const char*** paragraph)
{

}

size_t get_paragraph_sentence_count(const char*** paragraph)
{
    
}

const char** get_sentence_or_null(const size_t paragraph_index, const size_t sentence_index)
{

}

size_t get_sentence_word_count(const char** sentence)
{

}

int print_as_tree(const char* filename)
{

}
*/
