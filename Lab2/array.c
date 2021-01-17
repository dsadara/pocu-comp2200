#include "array.h"

int get_index_of(const int numbers[], const size_t element_count, const int num)
{
    size_t i;

    for (i = 0; i < element_count; ++i) {
        if (numbers[i] == num) {
            return i; 
        }
    }

    return -1;
}

int get_last_index_of(const int numbers[], const size_t element_count, const int num)
{
    size_t i;
    int last_index = -1;

    for (i = 0; i < element_count; ++i) {
        if (numbers[i] == num) {
            last_index = i; 
        }
    }

    return last_index;
}

int get_max_index(const int numbers[], const size_t element_count)
{
    size_t i;
    int max;
    int index;
    max = numbers[0];
    index = 0;
    
    if (element_count == 0) {
        return -1;
    }

    for (i = 0; i < element_count; ++i) {
        if (numbers[i] > max) {
            max = numbers[i];
            index = i;
        }
    }

    return index;
}

int get_min_index(const int numbers[], const size_t element_count)
{
    size_t i;
    int min;
    int index;
    min = numbers[0];
    index = 0;

    if (element_count == 0) {
        return -1;
    }

    for (i = 0; i < element_count; ++i) {
        if (numbers[i] < min) {
            min = numbers[i];
            index = i;
        }
    }

    return index;
}

int is_all_positive(const int numbers[], const size_t element_count)
{
    size_t i;
    int positive;
    positive = TRUE;

    if (element_count == 0) {
        return FALSE;
    }

    for (i = 0; i < element_count; ++i) {
        if (numbers[i] < 0) {
            positive = FALSE;
        }
    }

    return positive;
}

int has_even(const int numbers[], const size_t element_count)
{
    size_t i;
    int even;
    even = FALSE;

    for (i = 0; i < element_count; ++i) {
        if (numbers[i] % 2 == 0) {
            even = TRUE;
        }
    }

    return even;
}

int insert(int numbers[], const size_t element_count, const int num, const size_t pos)
{
    int i;

    if (element_count < pos) {
        return FALSE;
    }

    for (i = element_count - 1; i >= (int)pos; i--) {
        numbers[i + 1] = numbers[i];
    }
    numbers[pos] = num;

    return TRUE;
}

int remove_at(int numbers[], const size_t element_count, const size_t index)
{
    size_t i;

    if (element_count == 0) {
        return FALSE;
    }
    if (element_count <= index) {
        return FALSE;
    }

    for (i = index; i < element_count; ++i) {
        numbers[i] = numbers[i + 1];
    }

    return TRUE;
}
