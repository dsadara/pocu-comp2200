#include "pomoku.h"

size_t g_board_width = 15;
size_t g_board_height = 15;
size_t g_player0_score = 0;
size_t g_player1_score = 0;
int g_board[20][20];

size_t s_horizontal_score_before_black;
size_t s_horizontal_score_before_white;
size_t s_vertical_score_before_black;
size_t s_vertical_score_before_white;

void init_game(void)
{
    g_board_width = 15;
    g_board_height = 15;

    init_board();

    g_player0_score = 0;
    g_player1_score = 0;

    s_horizontal_score_before_white = 0;
    s_horizontal_score_before_black = 0;
    s_vertical_score_before_black = 0;
    s_vertical_score_before_white = 0;
}

size_t get_row_count(void)
{
    return g_board_height;
}

size_t get_column_count(void)
{
    return g_board_width;
}

int get_score(const color_t color)
{
    if (color == COLOR_BLACK) {
        return g_player0_score;
    } else if (color == COLOR_WHITE) {
        return g_player1_score;
    } else {
        return -1;
    }
}

int get_color(const size_t row, const size_t col)
{
    int stone_color = g_board[row][col];

    if (stone_color == 0) {
        return 0;
    } else if (stone_color == 1) {
        return 1;
    } else {
        return -1;
    }
}

int is_placeable(const size_t row, const size_t col)
{
    if (g_board[row][col] == 0 || g_board[row][col] == 1) {
        return FALSE;
    } else {
        return TRUE;
    }
}

int place_stone(const color_t color, const size_t row, const size_t col)
{
    size_t horizontal_score_temp;
    size_t vertical_score_temp;
    if(!is_placeable(row, col)) {
        return FALSE;
    }

    g_board[row][col] = color;

    if(color == COLOR_BLACK) {
        horizontal_score_temp = count_horizontal_chain_score(COLOR_BLACK, row);
        if (horizontal_score_temp != s_horizontal_score_before_black) {
            s_horizontal_score_before_black = horizontal_score_temp;
            g_player0_score += s_horizontal_score_before_black;
        }
        vertical_score_temp = count_vertical_chain_score(COLOR_BLACK, col);
        if (vertical_score_temp != s_vertical_score_before_black) {
            s_vertical_score_before_black = vertical_score_temp;
            g_player0_score += s_vertical_score_before_black;
        }
    } else if (color == COLOR_WHITE){
        horizontal_score_temp = count_horizontal_chain_score(COLOR_WHITE, row);
        if (horizontal_score_temp != s_horizontal_score_before_white) {
            s_horizontal_score_before_white = horizontal_score_temp;
            g_player1_score += s_horizontal_score_before_white;
        }

        vertical_score_temp = count_vertical_chain_score(COLOR_WHITE, col);
        if (vertical_score_temp != s_vertical_score_before_white) {
            s_vertical_score_before_white = vertical_score_temp;
            g_player1_score += s_vertical_score_before_white;
        }
    }
    return TRUE;
}

void init_board(void)
{
    size_t i;
    size_t j;

    for (i = 0; i < g_board_height; ++i) {
        for (j = 0; j < g_board_width; ++j) {
            g_board[i][j] = -1;
        }
    }
}

size_t count_horizontal_chain_score(const color_t color, const size_t row)
{
    size_t i;
    size_t score_sum = 0;
    size_t stone_sum = 0;

    for(i = 0; i < g_board_width; ++i) {
        if(g_board[row][i] == color) {
            stone_sum++;
        } else {
            if(stone_sum >= 5) {
                score_sum += get_score_per_stone(stone_sum);
            }
            stone_sum = 0;
        }
    }
    score_sum += get_score_per_stone(stone_sum);
    return score_sum;
}

size_t count_vertical_chain_score(const color_t color, const size_t col)
{
    size_t i;
    size_t score_sum = 0;
    size_t stone_sum = 0;

    for(i = 0; i < g_board_height; ++i) {
        if(g_board[i][col] == color) {
            stone_sum++;
        } else {
            if(stone_sum >= 5) {
                score_sum += get_score_per_stone(stone_sum);
            }
            stone_sum = 0;
        }
    }
    score_sum += get_score_per_stone(stone_sum);
    return score_sum;
}

size_t count_first_diagonal_chain_score(const color_t color, const size_t row, const size_t col)
{
    size_t i;
    size_t score_sum = 0;
    size_t stone_sum = 0;

    for()
    return score_sum;
}

size_t count_second_diagonal_chain_score(const color_t color, const size_t row, const, size_t col)
{
    
}
size_t get_score_per_stone(size_t stone_sum)
{
    if(stone_sum < 5 || stone_sum > 20) {
        return 0;
    }

    return stone_sum - 4;
}

