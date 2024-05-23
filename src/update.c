/*
** EPITECH PROJECT, 2024
** Corewar
** File description:
** The file containing the update functions
*/
/**
 * @file update.c
 * @brief The file containing the update functions
 */

#include "../include/corewar.h"

/**
 * @brief Update the program counter of a champion
 * @param champion The champion to update
 * @param value The value to add to the program counter
 * @return <b>void</b>
 */
void update_program_counter(champion_t *champion, int value)
{
    if (champion->address + value >= 6144)
        champion->program_counter = (champion->address + value) % 6144;
    else
        champion->program_counter = champion->address + value;
}

/**
 * @brief Update the carry of a champion
 * @param champion The champion to update
 * @param value The value to check
 * @return <b>void</b>
 */
void update_carry(champion_t *champion, int value)
{
    if (value == 0)
        champion->carry = 1;
    else
        champion->carry = 0;
}
