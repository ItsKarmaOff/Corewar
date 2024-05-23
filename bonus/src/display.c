/*
** EPITECH PROJECT, 2024
** Corewar
** File description:
** The file containing the display functions
*/
/**
 * @file display.c
 * @brief The file containing the display functions
 */

#include "../include/corewar.h"

/**
 * @brief Initialize the display
 * @param corewar The corewar structure
 * @return <b>void</b>
 */
void init_display(corewar_t *corewar)
{
    initscr();
    cbreak();
    noecho();
    nodelay(stdscr, TRUE);
    curs_set(FALSE);
    keypad(stdscr, TRUE);
    start_color();
    init_pair(0, COLOR_RED, COLOR_BLACK);
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_BLUE, COLOR_BLACK);
    init_pair(3, COLOR_GREEN, COLOR_BLACK);
    init_pair(4, COLOR_YELLOW, COLOR_BLACK);
    init_pair(5, COLOR_BLACK, COLOR_WHITE);
    init_pair(6, COLOR_RED, COLOR_WHITE);
    init_pair(7, COLOR_BLUE, COLOR_WHITE);
    init_pair(8, COLOR_GREEN, COLOR_WHITE);
    init_pair(9, COLOR_YELLOW, COLOR_WHITE);
    display_corewar(corewar);
}

/**
 * @brief Set the color of the texte
 * @param address The address of the cell
 * @param owner The owner of the cell
 * @return <b>void</b>
 */
void set_color(int address, char *owner)
{
    corewar_t *corewar = get_corewar();

    corewar->visual_color = 0;
    for (node_t *tmp = corewar->champions; tmp != NULL; tmp = tmp->next) {
        if (address == ((champion_t *)tmp->data)->address) {
            corewar->visual_color = 5;
            break;
        }
    }
    for (int index = 0; corewar->initial_champion[index] != NULL; index++) {
        if (owner == corewar->initial_champion[index]->prog_name) {
            corewar->visual_color += index + 1;
            break;
        }
    }
    attron(COLOR_PAIR(get_corewar()->visual_color));
}

/**
 * @brief Display the title of the game
 * @return <b>void</b>
 */
static void display_title(void)
{
    mvprintw(1, COLS / 8, "   _____ ____  _____  ________  "
        "        __     _____  ");
    mvprintw(2, COLS / 8, "  / ____/ __ \\|  __ \\|  ____\\"
        " \\        / /\\   |  __ \\ ");
    mvprintw(3, COLS / 8, " | |   | |  | | |__) | |__   \\"
        " \\  /\\  / /  \\  | |__) |");
    mvprintw(4, COLS / 8, " | |   | |  | |  _  /|  __|   \\"
        " \\/  \\/ / /\\ \\ |  _  / ");
    mvprintw(5, COLS / 8, " | |___| |__| | | \\ \\| |____   "
        "\\  /\\  / ____ \\| | \\ \\ ");
    mvprintw(6, COLS / 8, "  \\_____\\____/|_|  \\_\\______|"
        "   \\/  \\/_/    \\_\\_|  \\_\\"
        " by Nicolas TORO and Christophe VANDEVOIR\n\n");
}

/**
 * @brief Display the information of the game
 * @param corewar The corewar structure
 * @return <b>void</b>
 */
static void display_info(corewar_t *corewar)
{
    mvprintw(8, COLS / 4 - my_nbrlen(corewar->total_cycle)
        - my_nbrlen(corewar->nbr_cycle) + 5,
        "Cycle: %d / %d   |   Live: %d / 40\n",
        corewar->total_cycle, corewar->nbr_cycle, corewar->nbr_live);
    mvprintw(9, COLS / 4 + 7 - my_nbrlen(corewar->speed), "Speed: x%d   |"
        "   Press LEFT/RIGHT arrows to change the speed\n", corewar->speed);
    mvprintw(10, COLS / 4 - 5, "Press SPACE to start   |"
        "   Press SPACE to pause/continue\n");
    mvprintw(11, COLS / 4, "Press Q to stop   |"
        "   Press UP/DOWN arrows to move in the arena\n\n");
    mvprintw(13, 0, "Champion:");
    mvprintw(13, 65, "Number:");
    mvprintw(13, 75, "Address:");
    mvprintw(13, 90, "Alive:");
    mvprintw(13, 100, "Carry:");
    mvprintw(13, 110, "Cooldown:");
    mvprintw(13, 120, "Register:\n");
}

/**
 * @brief Display the register of the champion
 * @param champion_register The register of the champion
 * @return <b>void</b>
 */
void display_register(int *champion_register)
{
    wprintw(stdscr, "[");
    for (int i = 0; i < REG_NUMBER; i++) {
        wprintw(stdscr, "%x", champion_register[i]);
        if (i < REG_NUMBER - 1)
            wprintw(stdscr, ", ");
    }
    wprintw(stdscr, "]\n");
}

/**
 * @brief Display the champions
 * @param corewar The corewar structure
 * @return <b>void</b>
 */
void display_champions(corewar_t *corewar)
{
    int index = 14;

    for (node_t *tmp = corewar->champions;
    tmp != NULL && index < 34; tmp = tmp->next) {
        set_color(-1, ((champion_t *)tmp->data)->prog_name);
        mvprintw(index, 0, "%.50s", ((champion_t *)tmp->data)->prog_name);
        mvprintw(index, 65, "%d", ((champion_t *)tmp->data)->prog_number);
        if (((champion_t *)tmp->data)->address != 0)
            mvprintw(index, 75, "%#010x", ((champion_t *)tmp->data)->address);
        if (((champion_t *)tmp->data)->address == 0)
            mvprintw(index, 75, "0x00000000");
        mvprintw(index, 90, "%d", ((champion_t *)tmp->data)->alive);
        mvprintw(index, 100, "%d", ((champion_t *)tmp->data)->carry);
        mvprintw(index, 110, "%d\n", ((champion_t *)tmp->data)->cooldown);
        display_register(((champion_t *)tmp->data)->reg);
        attroff(COLOR_PAIR(corewar->visual_color));
        index += 2;
    }
    if (index >= 34)
        mvprintw(index, 0, "Too much champions to show...\n");
}

/**
 * @brief Display the current arena
 * @param corewar The corewar structure
 * @return <b>void</b>
 */
static void display_current_arena(corewar_t *corewar)
{
    node_t *tmp = get_arena_node(corewar->visual_index * 64);

    for (int i = 0; i < 64 * 32;) {
        if (((cell_t *) tmp->data)->address != 0)
            wprintw(stdscr, "%#010x: ", ((cell_t *) tmp->data)->address);
        if (((cell_t *) tmp->data)->address == 0)
            wprintw(stdscr, "0x00000000: ");
        for (int j = 0; j < 64; j++) {
            set_color(((cell_t *) tmp->data)->address,
                ((cell_t *) tmp->data)->owner);
            wprintw(stdscr, "%02x", ((cell_t *) tmp->data)->value);
            attroff(COLOR_PAIR(corewar->visual_color));
            tmp = tmp->next;
            i++;
        }
        wprintw(stdscr, "\n");
    }
}

/**
 * @brief Display the corewar
 * @param corewar The corewar structure
 * @return <b>void</b>
 */
void display_corewar(corewar_t *corewar)
{
    static int old_index = -1;
    static int old_speed = -1;

    if (corewar->pause == true &&
    old_index == corewar->visual_index && old_speed == corewar->speed)
        return;
    clear();
    display_title();
    display_info(corewar);
    display_champions(corewar);
    printw("\n");
    display_current_arena(corewar);
    refresh();
    old_index = corewar->visual_index;
    old_speed = corewar->speed;
}
