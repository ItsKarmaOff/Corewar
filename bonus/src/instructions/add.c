/*
** EPITECH PROJECT, 2024
** Corewar
** File description:
** The file containing the add function
*/
/**
 * @file add.c
 * @brief The file containing the add function
 */

#include "../../include/corewar.h"

/**
 * @brief The add function
 * @param champion The champion to execute the add function
 * @param address The address of the add function
 * @return <b>void</b>
 */
void exec_add(champion_t *champion, node_t *address)
{
    unsigned char coding_byte = get_int_from_address(address->next, 1);
    char value1 = get_int_from_address(address->next->next, 1);
    char value2 = get_int_from_address(address->next->next->next, 1);
    char register_choose =
        get_int_from_address(address->next->next->next->next, 1);

    update_program_counter(champion, 5);
    if (coding_byte != 0x54)
        return;
    if (value1 < 1 || value1 > 16 || value2 < 1 || value2 > 16
    || register_choose < 1 || register_choose > 16)
        return;
    champion->reg[register_choose - 1] =
        champion->reg[value1 - 1] + champion->reg[value2 - 1];
    update_carry(champion, champion->reg[register_choose - 1]);
}
