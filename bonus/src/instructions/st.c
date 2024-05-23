/*
** EPITECH PROJECT, 2024
** Corewar
** File description:
** The file containing the st function
*/
/**
 * @file st.c
 * @brief The file containing the st function
 */

#include "../../include/corewar.h"

/**
 * @brief Execute the st function with a register
 * @param champion The champion to execute the st function
 * @param address The address of the st function
 * @return <b>void</b>
 */
static void exec_register_st(champion_t *champion, node_t *address)
{
    char register_value = get_int_from_address(address->next->next, 1);
    char register_store =
        get_int_from_address(address->next->next->next, REG_SIZE);

    if (register_value < 1 || register_value > 16 ||
    register_store < 1 || register_store > 16)
        return;
    champion->reg[register_store - 1] = champion->reg[register_value - 1];
}

/**
 * @brief Execute the st function with an indirect
 * @param champion The champion to execute the st function
 * @param address The address of the st function
 * @return <b>void</b>
 */
static void exec_indirect_st(champion_t *champion, node_t *address)
{
    char register_value = get_int_from_address(address->next->next, 1);
    short register_store =
        get_int_from_address(address->next->next->next, IND_SIZE);
    node_t *address_to_store =
        get_arena_node(champion->address + register_store % IDX_MOD);

    if (register_value < 1 || register_value > 16)
        return;
    write_int_in_address(champion,
        address_to_store, champion->reg[register_value - 1]);
}

/**
 * @brief The st function
 * @param champion The champion to execute the st function
 * @param address The address of the st function
 * @return <b>void</b>
 */
void exec_st(champion_t *champion, node_t *address)
{
    unsigned char coding_byte = get_int_from_address(address->next, 1);

    if (get_code_byte_index(coding_byte, 0) == REG_CODE
    && get_code_byte_index(coding_byte, 1) == REG_CODE)
        exec_register_st(champion, address);
    if (get_code_byte_index(coding_byte, 0) == REG_CODE
    && get_code_byte_index(coding_byte, 1) == IND_CODE)
        exec_indirect_st(champion, address);
    update_program_counter(champion, 2 +
        get_size_of_coding_byte(coding_byte, false));
}
