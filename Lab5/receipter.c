#include "receipter.h"

char g_items[10][ITEM_STR_LENGTH + 1];
double g_price[10] = { 0, };
double g_tip = 0;
char g_message[MESSAGE_LENGTH + 1];
size_t g_item_num = 0;
size_t g_order_num = 0;

int add_item(const char* name, double price)
{
    if (price > 999.99 || g_item_num >= 10) {
        return FALSE;
    }

    strncpy(g_items[g_item_num], name, ITEM_STR_LENGTH);
    g_items[g_item_num][ITEM_STR_LENGTH] = '\0';
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
    strncpy(g_message, message, MESSAGE_LENGTH);
    g_message[MESSAGE_LENGTH] = '\0';  

    if (strlen(g_message) > 50) {
        memmove(g_message + 51, g_message + 50, strlen(g_message + 50));
        g_message[50] = '\n';
    }
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
    fprintf(stream, "%04d-%02d-%02d %02d:%02d:%02d                          %05zd\n", local->tm_year + 1900, local->tm_mon + 1, local->tm_mday, local->tm_hour, local->tm_min, local->tm_sec, g_order_num);
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
