/*
** EPITECH PROJECT, 2024
** Corewar
** File description:
** The file containing the touch functions
*/
/**
 * @file touch.c
 * @brief The file containing the touch functions
 */

#include "../include/corewar.h"

/**
 * @brief Display the invalid size message
 * @return <b>void</b>
 */
static void display_invalid_size(void)
{
    erase();
    move(LINES / 2 - 1 / 2, COLS / 2 - 29 / 2);
    printw("Please, enlarge the terminal !");
    refresh();
}

/**
 * @brief Check the keyboard arrows
 * @param corewar The corewar structure
 * @param touch The touch to check
 * @return <b>void</b>
 */
static void keyboard_arrows(corewar_t *corewar, int touch)
{
    if (touch == KEY_UP && corewar->visual_index > 0)
        corewar->visual_index -= 1;
    if (touch == KEY_DOWN && corewar->visual_index < 96 - 32)
        corewar->visual_index += 1;
    if (touch == KEY_LEFT && corewar->speed > 1)
        corewar->speed -= 1;
    if (touch == KEY_RIGHT && corewar->speed < 25)
        corewar->speed += 1;
}

/**
 * @brief Check the touch
 * @param corewar The corewar structure
 * @return <b>int</b> <u>1</u> if the terminal is too small, <u>0</u> otherwise
 */
int check_touch(corewar_t *corewar)
{
    int touch = getch();

    if (touch == 'q') {
        endwin();
        free_corewar();
        exit(0);
    }
    if (touch == ' ')
        corewar->pause = !corewar->pause;
    keyboard_arrows(corewar, touch);
    if (50 > LINES || 145 > COLS) {
        display_invalid_size();
        return 1;
    }
    return 0;
}
