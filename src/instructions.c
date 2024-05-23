/*
** EPITECH PROJECT, 2024
** Corewar
** File description:
** The file containing the instructions functions
*/
/**
 * @file instructions.c
 * @brief The file containing the instructions functions
 */

#include "../include/corewar.h"

/**
 * @brief Execute the instructions
 * @param champion The champion to execute the instructions
 * @return <b>void</b>
 */
void execute_instructions(champion_t *champion)
{
    static void (*instructions[16])(champion_t *champion, node_t *address) = {
        &exec_live, &exec_ld, &exec_st, &exec_add, &exec_sub, &exec_and,
        &exec_or, &exec_xor, &exec_zjmp, &exec_ldi, &exec_sti, &exec_fork,
        &exec_lld, &exec_lldi, &exec_lfork, &exec_aff
    };
    node_t *address = NULL;

    if (champion->cooldown > 0) {
        champion->cooldown--;
        return;
    }
    champion->address = champion->program_counter;
    address = get_arena_node(champion->address);
    if (-1 < ((cell_t *)address->data)->value - 1 &&
    ((cell_t *)address->data)->value - 1 < 0x10) {
        champion->cooldown =
            op_tab[((cell_t *)address->data)->value - 1].nbr_cycles;
        instructions[((cell_t *)address->data)->value - 1](champion, address);
    } else
        champion->program_counter++;
}

/**
 * @brief Get int from address
 * @param address The address to get the int
 * @param size The size of the int
 * @return <b>int</b> The int
 */
int get_int_from_address(node_t *address, int size)
{
    int result = 0;

    for (int index = 0; index < size; index++) {
        result = result * 0x100 + ((cell_t *)address->data)->value;
        address = address->next;
    }
    return result;
}

/**
 * @brief Write int in address
 * @param champion The champion to write the int
 * @param address The address to write the int
 * @param value The value to write
 */
void write_int_in_address(champion_t *champion, node_t *address, int value)
{
    unsigned char *bytes = (unsigned char *)&value;

    for (int index = 3; index > -1; index--) {
        ((cell_t *)address->data)->value = bytes[index];
        ((cell_t *)address->data)->owner = champion->prog_name;
        address = address->next;
    }
}

/**
 * @brief Read int in address
 * @param address The address to read the int
 * @param size The size of the int
 * @return <b>int</b> The int read
 */
int read_int_in_address(node_t *address, int size)
{
    int result = 0;

    for (int index = 0; index < size; index++) {
        result = result * 0x100 + ((cell_t *)address->data)->value;
        address = address->next;
    }
    return result;
}
