/*
** EPITECH PROJECT, 2024
** Corewar
** File description:
** The file containing the lfork function
*/
/**
 * @file lfork.c
 * @brief The file containing the lfork function
 */

#include "../../include/corewar.h"

/**
 * @brief Fork the register of a champion
 * @param champion The champion to fork
 * @param new_register The new register
 * @return The forked register
 */
static int *fork_register(champion_t *champion, int *new_register)
{
    for (int i = 0; i < 16; i++)
        new_register[i] = champion->reg[i];
    return new_register;
}

/**
 * @brief Fork a champion
 * @param champion The champion to fork
 * @return The forked champion
 */
static champion_t *fork_champion(champion_t *champion)
{
    champion_t *new_champion = CALLOC(1, sizeof(champion_t));

    new_champion->address = champion->address;
    new_champion->carry = champion->carry;
    new_champion->prog_name = champion->prog_name;
    new_champion->prog_size = champion->prog_size;
    new_champion->alive = champion->alive;
    new_champion->prog_number = champion->prog_number;
    new_champion->cooldown = champion->cooldown;
    new_champion->comment = champion->comment;
    fork_register(champion, new_champion->reg);
    return new_champion;
}

/**
 * @brief The lfork function
 * @param champion The champion to execute the lfork function
 * @param address The address of the lfork function
 * @return <b>void</b>
 */
void exec_lfork(champion_t *champion, node_t *address)
{
    short value = get_int_from_address(address->next, 2);
    champion_t *new_champion = fork_champion(champion);

    my_push_back(&get_corewar()->champions, new_champion, UNKNOWN);
    new_champion->program_counter = new_champion->address + value;
    update_program_counter(champion, 3);
}
