#include "receipter.h"

char g_items[10][26];
double g_price[10] = { 0, };
double g_tip = 0;
char g_message[80];
size_t g_item_num = 0;
size_t g_order_num = 0;

int add_item(const char* name, double price)
{
    if (strlen(name) > 25 || price > 999.99 || g_item_num >= 10) {
        return FALSE;
    }

    strcpy(g_items[g_item_num], name);
    g_price[g_item_num] = price;
    g_item_num++;

    return TRUE;
}

void set_tip(double tip)
{
    if (tip < 0) {
        return;
    }

    g_tip += tip;
}

void set_message(const char* message)
{
    size_t length = strlen(message);
    char null_char = '\0';
    if (length > 75) {
        return;
    } else if (length > 50) {
        strcpy(g_message, message);
        memmove(g_message + 50, g_message + 49, strlen(g_message + 49));
        memmove(g_message + 49, &null_char, 1);
        return;
    }

    strcpy(g_message, message);
}

int print_receipt(const char* filename, time_t timestamp)
{
    FILE* stream;
    struct tm* local;
    double sub_total = 0;
    double tax;
    size_t i;

    if (g_item_num == 0) {
        g_tip = 0;
        g_message[0] = '\0';
        return FALSE;
    }

    local = localtime(&timestamp);
    stream = fopen(filename, "w");

    fprintf(stream, "Charles' Seafood\n");
    fprintf(stream, "--------------------------------------------------\n");
    fprintf(stream, "%04d-%02d-%02d %02d:%02d:%02d                          %05zd\n",
    local->tm_year + 1900, local->tm_mon + 1, local->tm_mday, local->tm_hour, local->tm_min, local->tm_sec, g_order_num);
    fprintf(stream, "--------------------------------------------------\n");

    for (i = 0; i < g_item_num; i++) {
        fprintf(stream, "%33s%17.2f\n", g_items[i], g_price[i]);
        sub_total += g_price[i];
    }
    tax = sub_total * 0.05;
    tax = (int)((tax + 0.005) * 100) / 100.0;

    fprintf(stream, "\n");
    fprintf(stream, "                         Subtotal%17.2f\n", sub_total);

    if (g_tip != 0) {
        fprintf(stream, "                              Tip%17.2f\n", g_tip);
    }

    fprintf(stream, "                              Tax%17.2f\n", tax);
    fprintf(stream, "                            Total%17.2f\n", sub_total + g_tip + tax);
    fprintf(stream, "\n");

    if (strlen(g_message) != 0) {
        fprintf(stream, "%s\n", g_message);
    }

    fprintf(stream, "==================================================\n");
    fprintf(stream, "                                        Tax#-51234");
    fflush(stream);
    fclose(stream);

    g_tip = 0;
    g_item_num = 0;
    g_order_num++;
    g_message[0] = '\0';

    return TRUE;
}
