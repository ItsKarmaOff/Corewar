/*
** EPITECH PROJECT, 2024
** Corewar
** File description:
** The file containing the live function
*/
/**
 * @file live.c
 * @brief The file containing the live function
 */

#include "../../include/corewar.h"

/**
 * @brief The live function
 * @param champion The champion to execute the live function
 * @param address The address of the live function
 * @return <b>void</b>
 */
void exec_live(champion_t *champion, node_t *address)
{
    int champion_number = get_int_from_address(address->next, 4);
    champion_t *champion_live = get_champion_by_number(champion_number);

    update_program_counter(champion, 5);
    if (champion_live == NULL)
        return;
    get_corewar()->nbr_live++;
    if (get_corewar()->nbr_live >= NBR_LIVE) {
        get_corewar()->nbr_cycle -= CYCLE_DELTA;
        get_corewar()->nbr_live = 0;
    }
    if (champion->prog_number == champion_number)
        champion->alive = 1;
    my_printf("The player %d(%s) is alive.\n",
        champion_live->prog_number, champion_live->prog_name);
}
