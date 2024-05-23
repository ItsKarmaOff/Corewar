/*
** EPITECH PROJECT, 2024
** Corewar
** File description:
** The file containing the ldi function
*/
/**
 * @file live.c
 * @brief The file containing the ldi function
 */

#include "../../include/corewar.h"

/**
 * @brief Check the arguments of the function
 * @param address The address to start
 * @param coding_byte The coding byte
 * @return <b>int</b> The error code
 */
static int check_args(node_t *address, char coding_byte)
{
    char type = 0;

    for (int i = 0; i < 3; i++) {
        type = get_code_byte_index(coding_byte, i);
        if (type == 0)
            break;
        if (type == REG_CODE &&
            (get_int_from_address(address, 1) < 1 ||
                get_int_from_address(address, 1) > 16))
            return 1;
        if ((i == 2 && type != REG_CODE) || (i == 1 && type == IND_CODE))
            return 1;
        for (int j = 0; j < get_size_from_type(type, true); j++)
            address = address->next;
    }
    type = get_code_byte_index(coding_byte, 3);
    if (type != 0)
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
 * @brief Get the register choose
 * @param address The address to start
 * @param coding_byte The coding byte
 * @return <b>char</b> The register choose
 */
static char get_register_choose(node_t *address, char coding_byte)
{
    for (int i = 0; i < get_size_from_type(get_code_byte_index(coding_byte, 0),
    true) + get_size_from_type(get_code_byte_index(coding_byte, 1),
    true) + 2; i++)
        address = address->next;
    return get_int_from_address(address, 1);
}

/**
 * @brief The ldi function
 * @param champion The champion to execute the ldi function
 * @param address The address of the ldi function
 * @return <b>void</b>
 */
void exec_ldi(champion_t *champion, node_t *address)
{
    unsigned char coding_byte = get_int_from_address(address->next, 1);
    int register_choose = 0;
    int value1 = 0;
    int value2 = 0;

    update_program_counter(champion, 2 +
        get_size_of_coding_byte(coding_byte, true));
    if (check_args(address->next->next, coding_byte))
        return;
    value1 = get_value(champion, address, 2,
        get_code_byte_index(coding_byte, 0));
    value2 = get_value(champion, address,
        get_size_from_type(get_code_byte_index(coding_byte, 0), true) + 2,
        get_code_byte_index(coding_byte, 1));
    register_choose = get_register_choose(address, coding_byte);
    champion->reg[register_choose - 1] = read_int_in_address(
        get_arena_node(champion->address + (value1 + value2) % IDX_MOD), 4);
    update_carry(champion, champion->reg[register_choose - 1]);
}
