/*
** EPITECH PROJECT, 2024
** Corewar
** File description:
** The file containing the coding_byte functions
*/
/**
 * @file coding_byte.c
 * @brief The file containing the coding_byte functions
 */

#include "../include/corewar.h"

/**
 * @brief Get the type of byte with the coding byte at the index
 * @param coding_byte The coding byte to get the index
 * @param index The index of the coding byte value
 * @return <b>char</b> The type of byte
 */
char get_code_byte_index(char coding_byte, int index)
{
    return (coding_byte >> (2 * (3 - index))) & 0x03;
}

/**
 * @brief Get the size of the type
 * @param type The type to get the size
 * @param max_size The max size of the type
 * @return <b>char</b> The size of the type
 */
char get_size_from_type(char type, bool max_size)
{
    if (type == REG_CODE)
        return REG_SIZE;
    if (type == IND_CODE || (type == DIR_CODE && max_size))
        return IND_SIZE;
    if (type == DIR_CODE)
        return DIR_SIZE;
    return 0;
}

/**
 * @brief Get the size of the coding byte
 * @param coding_byte The coding byte to get the size
 * @param max_size The max size of the coding byte
 * @return <b>char</b> The size of the coding byte
 */
char get_size_of_coding_byte(char coding_byte, bool max_size)
{
    char size = 0;

    for (int index = 0; index < 4; index++)
        size += get_size_from_type(
            get_code_byte_index(coding_byte, index), max_size);
    return size;
}
