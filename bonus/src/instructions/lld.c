/*
** EPITECH PROJECT, 2024
** Corewar
** File description:
** The file containing the lld function
*/
/**
 * @file lld.c
 * @brief The file containing the lld function
 */

#include "../../include/corewar.h"

/**
 * @brief Execute the direct lld function
 * @param champion The champion to execute the lld function
 * @param address The address of the lld function
 * @return <b>void</b>
 */
static void exec_direct_lld(champion_t *champion, node_t *address)
{
    int value = get_int_from_address(address->next->next, DIR_SIZE);
    char register_choose = get_int_from_address(
        address->next->next->next->next->next->next, 1);

    if (register_choose < 1 || register_choose > 16)
        return;
    champion->reg[register_choose - 1] = value;
    update_carry(champion, champion->reg[register_choose - 1]);
}

/**
 * @brief Execute the indirect lld function
 * @param champion The champion to execute the lld function
 * @param address The address of the lld function
 * @return <b>void</b>
 */
static void exec_indirect_lld(champion_t *champion, node_t *address)
{
    short index = get_int_from_address(address->next->next, IND_SIZE);
    char register_choose = get_int_from_address(
        address->next->next->next->next, 1);

    if (register_choose < 1 || register_choose > 16)
        return;
    champion->reg[register_choose - 1] = read_int_in_address(
        get_arena_node(champion->address + index), 4);
    update_carry(champion, champion->reg[register_choose - 1]);
}

/**
 * @brief The lld function
 * @param champion The champion to execute the lld function
 * @param address The address of the lld function
 * @return <b>void</b>
 */
void exec_lld(champion_t *champion, node_t *address)
{
    unsigned char coding_byte = get_int_from_address(address->next, 1);

    if (get_code_byte_index(coding_byte, 0) == DIR_CODE
    && get_code_byte_index(coding_byte, 1) == REG_CODE)
        exec_direct_lld(champion, address);
    if (get_code_byte_index(coding_byte, 0) == IND_CODE
    && get_code_byte_index(coding_byte, 1) == REG_CODE)
        exec_indirect_lld(champion, address);
    update_program_counter(champion, 2 +
        get_size_of_coding_byte(coding_byte, false));
}
