/*
** EPITECH PROJECT, 2024
** Corewar
** File description:
** The file containing the zjmp function
*/
/**
 * @file zjmp.c
 * @brief The zjmp containing the live function
 */

#include "../../include/corewar.h"

/**
 * @brief The zjmp function
 * @param champion The champion to execute the zjmp function
 * @param address The address of the zjmp function
 * @return <b>void</b>
 */
void exec_zjmp(champion_t *champion, node_t *address)
{
    short champion_number = get_int_from_address(address->next, 2);

    if (champion->carry)
        update_program_counter(champion, champion_number % IDX_MOD);
    else
        update_program_counter(champion, 3);
}
