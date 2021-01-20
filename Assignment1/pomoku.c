#include "pomoku.h"

size_t g_board_width = 15;
size_t g_board_height = 15;
size_t g_player0_score = 0;
size_t g_player1_score = 0;
int g_board[20][20];

size_t g_horizontal_score_before_black;
size_t g_horizontal_score_before_white;
size_t g_vertical_score_before_black;
size_t g_vertical_score_before_white;
size_t g_left_diagonal_score_before_black;
size_t g_left_diagonal_score_before_white;
size_t g_right_diagonal_score_before_black;
size_t g_right_diagonal_score_before_white;

void init_game(void)
{
    g_board_width = 15;
    g_board_height = 15;

    init_board();

    g_player0_score = 0;
    g_player1_score = 0;

    g_horizontal_score_before_white = 0;
    g_horizontal_score_before_black = 0;
    g_vertical_score_before_black = 0;
    g_vertical_score_before_white = 0;
    g_left_diagonal_score_before_black = 0;
    g_left_diagonal_score_before_white = 0;
    g_right_diagonal_score_before_black = 0;
    g_right_diagonal_score_before_white = 0;
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
        if (row < g_board_height && col < g_board_width) {
            return TRUE;
        }
        return FALSE;
    }
}

int place_stone(const color_t color, const size_t row, const size_t col)
{
    size_t horizontal_score_temp;
    size_t vertical_score_temp;
    size_t left_diagonal_score_temp;
    size_t right_diagonal_score_temp;

    if (!is_placeable(row, col)) {
        return FALSE;
    }

    g_board[row][col] = color;

    if (color == COLOR_BLACK) {

        horizontal_score_temp = count_horizontal_chain_score(COLOR_BLACK, row);
        if (horizontal_score_temp != g_horizontal_score_before_black) {
            g_horizontal_score_before_black = horizontal_score_temp;
            g_player0_score += g_horizontal_score_before_black;
        }

        vertical_score_temp = count_vertical_chain_score(COLOR_BLACK, col);
        if (vertical_score_temp != g_vertical_score_before_black) {
            g_vertical_score_before_black = vertical_score_temp;
            g_player0_score += g_vertical_score_before_black;
        }

        left_diagonal_score_temp = count_left_diagonal_chain_score(COLOR_BLACK, row, col);
        if (left_diagonal_score_temp != g_left_diagonal_score_before_black) {
            g_left_diagonal_score_before_black = left_diagonal_score_temp;
            g_player0_score += g_left_diagonal_score_before_black;
        }

        right_diagonal_score_temp = count_right_diagonal_chain_score(COLOR_BLACK, row, col);
        if (right_diagonal_score_temp != g_right_diagonal_score_before_black) {
            g_right_diagonal_score_before_black = right_diagonal_score_temp;
            g_player0_score += g_right_diagonal_score_before_black;
        }

    } else if (color == COLOR_WHITE) {

        horizontal_score_temp = count_horizontal_chain_score(COLOR_WHITE, row);
        if (horizontal_score_temp != g_horizontal_score_before_white) {
            g_horizontal_score_before_white = horizontal_score_temp;
            g_player1_score += g_horizontal_score_before_white;
        }

        vertical_score_temp = count_vertical_chain_score(COLOR_WHITE, col);
        if (vertical_score_temp != g_vertical_score_before_white) {
            g_vertical_score_before_white = vertical_score_temp;
            g_player1_score += g_vertical_score_before_white;
        }

        left_diagonal_score_temp = count_left_diagonal_chain_score(COLOR_WHITE, row, col);
        if (left_diagonal_score_temp != g_left_diagonal_score_before_white) {
            g_left_diagonal_score_before_white = left_diagonal_score_temp;
            g_player1_score += g_left_diagonal_score_before_white;
        }

        right_diagonal_score_temp = count_right_diagonal_chain_score(COLOR_WHITE, row, col);
        if (right_diagonal_score_temp != g_right_diagonal_score_before_white) {
            g_right_diagonal_score_before_white = right_diagonal_score_temp;
            g_player1_score += g_right_diagonal_score_before_white;
        }
    } else {
        return FALSE;
    }
    return TRUE;
}

void init_board(void)
{
    size_t i;
    size_t j;

    for (i = 0; i < 20; ++i) {
        for (j = 0; j < 20; ++j) {
            g_board[i][j] = -1;
        }
    }
}

size_t count_horizontal_chain_score(const color_t color, const size_t row)
{
    size_t i;
    size_t score_sum = 0;
    size_t stone_sum = 0;

    for (i = 0; i < g_board_width; ++i) {
        if (g_board[row][i] == color) {
            stone_sum++;
        } else {
            if (stone_sum >= 5) {
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

    for (i = 0; i < g_board_height; ++i) {
        if (g_board[i][col] == color) {
            stone_sum++;
        } else {
            if (stone_sum >= 5) {
                score_sum += get_score_per_stone(stone_sum);
            }
            stone_sum = 0;
        }
    }
    score_sum += get_score_per_stone(stone_sum);
    return score_sum;
}

size_t get_score_per_stone(size_t stone_sum)
{
    if (stone_sum < 5 || stone_sum > 20) {
        return 0;
    }

    return stone_sum - 4;
}


size_t count_left_diagonal_chain_score(const color_t color, const size_t row, const size_t col)
{
    size_t i;
    size_t score_sum = 0;
    size_t stone_sum = 1;
    size_t row_upleft;
    size_t col_upleft;
    size_t row_downright;
    size_t col_downright;
    size_t min_diagonal_length = (g_board_height > g_board_width) ? g_board_width : g_board_height;
    int downright = TRUE;
    int upleft = TRUE;

    for (i = 1; i <= min_diagonal_length; i++) {
        row_downright = row + i;
        col_downright = col + i;
        row_upleft = row - i;
        col_upleft = col - i;

        if (check_boundary(row_downright, col_downright) && g_board[row_downright][col_downright] == color) {
            stone_sum++;
        } else {
            downright = FALSE;
        }

        if (check_boundary(row_upleft, col_upleft) && g_board[row_upleft][col_upleft] == color) {
            stone_sum++;
        } else {
            upleft = FALSE;
        }

        if (!downright && !upleft) {
            if (stone_sum >= 5) {
                score_sum += get_score_per_stone(stone_sum);
            }
            stone_sum = 0;
            downright = TRUE;
            upleft = TRUE;
        }
    }
    score_sum += get_score_per_stone(stone_sum);
    return score_sum;
}

size_t count_right_diagonal_chain_score(const color_t color, const size_t row, const size_t col)
{
    size_t i;
    size_t score_sum = 0;
    size_t stone_sum = 1;
    size_t row_downleft;
    size_t col_downleft;
    size_t row_upright;
    size_t col_upright;
    size_t min_diagonal_length = (g_board_height > g_board_width) ? g_board_width : g_board_height;
    int downleft = TRUE;
    int upright = TRUE;

    for (i = 1; i <= min_diagonal_length; i++) {
        row_downleft = row + i;
        col_downleft = col - i;
        row_upright = row - i;
        col_upright = col + i;

        if (check_boundary(row_downleft, col_downleft) && g_board[row_downleft][col_downleft] == color) {
            stone_sum++;
        } else {
            downleft = FALSE;
        }

        if (check_boundary(row_upright, col_upright) && g_board[row_upright][col_upright] == color) {
            stone_sum++;
        } else {
            upright = FALSE;
        }

        if (!downleft && !upright) {
            if (stone_sum >= 5) {
                score_sum += get_score_per_stone(stone_sum);
            }
            stone_sum = 0;
            downleft = TRUE;
            upright = TRUE;
        }
    }
    score_sum += get_score_per_stone(stone_sum);
    return score_sum;
}

size_t check_boundary(const size_t row, const size_t col)
{
    if (row >= g_board_height || col >= g_board_width) {
        return FALSE;
    }

    return TRUE;
}

int insert_row(const color_t color, const size_t row)
{
    size_t i;
    size_t j;

    if (row > g_board_height || g_board_height >= 20) {
        return FALSE;
    }

    if (color == COLOR_BLACK) {
        if (g_player0_score < 3) {
            return FALSE;
        }
        g_player0_score -= 3;
    } else if (color == COLOR_WHITE) {
        if (g_player1_score < 3) {
            return FALSE;
        }
        g_player1_score -= 3;
    } else {
        return FALSE;
    }


    for (i = g_board_height; i > row; i--) {
        for (j = 0; j < g_board_width; j++) {
            g_board[i][j] = g_board[i - 1][j];
        }
    }

    for (i = 0; i < g_board_width; i++) {
        g_board[row][i] = -1;
    }

    g_board_height++;
    return TRUE;
}

int insert_column(const color_t color, const size_t col)
{
    size_t i;
    size_t j;

    if (col > g_board_width || g_board_width >= 20) {
        return FALSE;
    }

    if (color == COLOR_BLACK) {
        if (g_player0_score < 3) {
            return FALSE;
        }
        g_player0_score -= 3;
    } else if (color == COLOR_WHITE) {
        if (g_player1_score < 3) {
            return FALSE;
        }
        g_player1_score -= 3;
    } else {
        return FALSE;
    }

    for (i = g_board_width; i > col; i--) {
        for (j = 0; j < g_board_height; j++) {
            g_board[j][i] = g_board[j][i - 1];
        }
    }

    for (i = 0; i < g_board_height; i++) {
        g_board[i][col] = -1;
    }

    g_board_width++;
    return TRUE;
}

int remove_row(const color_t color, const size_t row)
{
    size_t i;
    size_t j;

    if (row >= g_board_height || g_board_height <= 10) {
        return FALSE;
    }

    if (color == COLOR_BLACK) {
        if (g_player0_score < 3) {
            return FALSE;
        }
        g_player0_score -= 3;
    }

    if (color == COLOR_WHITE) {
        if (g_player1_score < 3) {
            return FALSE;
        }
        g_player1_score -= 3;
    }

    for (i = row; i < g_board_height; i++) {
        for (j = 0; j < g_board_width; j++) {
            g_board[i][j] = g_board[i + 1][j];
        }
    }

    g_board_height--;
    return TRUE;
}

int remove_column(const color_t color, const size_t col)
{
    size_t i;
    size_t j;

    if (col >= g_board_width || g_board_width <= 10) {
        return FALSE;
    }

    if (color == COLOR_BLACK) {
        if (g_player0_score < 3) {
            return FALSE;
        }
        g_player0_score -= 3;
    }

    if (color == COLOR_WHITE) {
        if (g_player1_score < 3) {
            return FALSE;
        }
        g_player1_score -= 3;
    }

    for (i = col; i < g_board_width; i++) {
        for (j = 0; j < g_board_height; j++) {
            g_board[j][i] = g_board[j][i + 1];
        }
    }

    g_board_width--;
    return TRUE;
}

int swap_rows(const color_t color, const size_t row0, const size_t row1)
{
    size_t i;
    int temp;

    if (row0 >= g_board_height || row1 >= g_board_height) {
        return FALSE;
    }

    if (color == COLOR_BLACK) {
        if (g_player0_score < 2) {
            return FALSE;
        }
        g_player0_score -= 2;
    }

    if (color == COLOR_WHITE) {
        if (g_player1_score < 2) {
            return FALSE;
        }
        g_player1_score -= 2;
    }

    for (i = 0; i < g_board_width; i++) {
        temp = g_board[row0][i];
        g_board[row0][i] = g_board[row1][i];
        g_board[row1][i] = temp;
    }

    return TRUE;
}

int swap_columns(const color_t color, const size_t col0, const size_t col1)
{
    size_t i;
    int temp;

    if (col0 >= g_board_height || col1 >= g_board_height) {
        return FALSE;
    }

    if (color == COLOR_BLACK) {
        if (g_player0_score < 2) {
            return FALSE;
        }
        g_player0_score -= 2;
    }

    if (color == COLOR_WHITE) {
        if (g_player1_score < 2) {
            return FALSE;
        }
        g_player1_score -= 2;
    }

    for (i = 0; i < g_board_height; i++) {
        temp = g_board[i][col0];
        g_board[i][col0] = g_board[i][col1];
        g_board[i][col1] = temp;
    }

    return TRUE;
}

int copy_row(const color_t color, const size_t src, const size_t dst)
{
    size_t i;

    if (src >= g_board_width || dst >= g_board_width) {
        return FALSE;
    }

    if (color == COLOR_BLACK) {
        if (g_player0_score < 4) {
            return FALSE;
        }
        g_player0_score -= 4;
    }

    if (color == COLOR_WHITE) {
        if (g_player1_score < 4) {
            return FALSE;
        }
        g_player1_score -= 4;
    }

    for (i = 0; i < g_board_width; i++) {
        g_board[dst][i] = g_board[src][i];
    }

    return TRUE;
}

int copy_column(const color_t color, const size_t src, const size_t dst)
{
    size_t i;

    if (src >= g_board_height || dst >= g_board_width) {
        return FALSE;
    }

    if (color == COLOR_BLACK) {
        if (g_player0_score < 4) {
            return FALSE;
        }
        g_player0_score -= 4;
    }

    if (color == COLOR_WHITE) {
        if (g_player1_score < 4) {
            return FALSE;
        }
        g_player1_score -= 4;
    }

    for (i = 0; i < g_board_height; i++) {
        g_board[i][dst] = g_board[i][src];
    }

    return TRUE;
}
