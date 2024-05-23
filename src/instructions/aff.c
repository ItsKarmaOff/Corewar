/*
** EPITECH PROJECT, 2024
** Corewar
** File description:
** The file containing the aff function
*/
/**
 * @file aff.c
 * @brief The file containing the aff function
 */

#include "../../include/corewar.h"

/**
 * @brief The aff function
 * @param champion The champion to execute the aff function
 * @param address The address of the aff function
 * @return <b>void</b>
 */
void exec_aff(champion_t *champion, node_t *address)
{
    char coding_byte = get_int_from_address(address->next, 1);
    char register_choose = get_int_from_address(address->next->next, 1);

    if (coding_byte != 0x40 || register_choose < 1 || register_choose > 16)
        return;
    my_printf("%c\n", champion->reg[register_choose - 1]);
    update_program_counter(champion, 3);
}
