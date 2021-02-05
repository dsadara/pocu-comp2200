#ifndef RECEIPTER_H
#define RECEIPTER_H


#include <stdio.h>
#include <string.h>
#include <time.h>

#define TRUE (1)
#define FALSE (0)
#define ITEM_STR_LENGTH (25)

size_t my_strlen(const char* str, const char* delims);

int add_item(const char* name, double price);

void set_tip(double tip);

void set_message(const char* message);

int print_receipt(const char* filename, time_t timestamp);

#endif /* RECEIPTER_H */
