/*
** EPITECH PROJECT, 2024
** Corewar
** File description:
** The file containing the sti function
*/
/**
 * @file sti.c
 * @brief The file containing the sti function
 */

#include "../../include/corewar.h"

/**
 * @brief Check if the arguments are valid
 * @param address The address of the sti function
 * @param coding_byte The coding byte of the sti function
 * @return <b>int</b>
 */
static int check_args(node_t *address, int coding_byte)
{
    char value = get_int_from_address(address->next->next, 1);

    if (value < 1 || value > 16)
        return 1;
    value = get_int_from_address(address->next->next->next, 1);
    if (get_code_byte_index(coding_byte, 1) == REG_CODE
    && (value < 1 || value > 16))
        return 1;
    value = get_int_from_address(address->next->next->next->next, 1);
    if (get_code_byte_index(coding_byte, 1) == REG_CODE &&
    get_code_byte_index(coding_byte, 2) == REG_CODE
    && (value < 1 || value > 16))
        return 1;
    value = get_int_from_address(address->next->next->next->next->next, 1);
    if (get_code_byte_index(coding_byte, 1) != REG_CODE
    && get_code_byte_index(coding_byte, 2) == REG_CODE
    && (value < 1 || value > 16))
        return 1;
    return 0;
}

/**
 * @brief Get the value of the argument
 * @param champion The champion to get the value
 * @param address The address to start
 * @param start The start of the argument
 * @param coding_byte The coding byte
 * @return <b>int</b> The value of the argument
 */
static int get_value(champion_t *champion, node_t *address,
    int start, int coding_byte)
{
    int value = 0;

    for (int i = 0; i < start; i++)
        address = address->next;
    value = get_int_from_address(address,
        get_size_from_type(coding_byte, true));
    if (coding_byte == REG_CODE)
        value = champion->reg[value - 1];
    return value;
}

/**
 * @brief The sti function
 * @param champion The champion to execute the sti function
 * @param address The address of the sti function
 * @return <b>void</b>
 */
void exec_sti(champion_t *champion, node_t *address)
{
    unsigned char coding_byte = get_int_from_address(address->next, 1);
    char register_choose = get_int_from_address(address->next->next, 1);
    int value1 = 0;
    int value2 = 0;

    update_program_counter(champion, 2 +
        get_size_of_coding_byte(coding_byte, true));
    if (get_code_byte_index(coding_byte, 0) != REG_CODE
    || check_args(address, coding_byte))
        return;
    value1 = get_value(champion, address, 3,
        get_code_byte_index(coding_byte, 1));
    value2 = get_value(champion, address,
        get_size_from_type(get_code_byte_index(coding_byte, 1), true) + 3,
        get_code_byte_index(coding_byte, 2));
    write_int_in_address(champion,
        get_arena_node(champion->address + (value1 + value2) % IDX_MOD),
        champion->reg[register_choose - 1]);
}
