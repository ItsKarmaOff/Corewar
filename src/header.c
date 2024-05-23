/*
** EPITECH PROJECT, 2024
** Corewar
** File description:
** The file containing the header functions
*/
/**
 * @file header.c
 * @brief The file containing the header functions
 */

#include "../include/corewar.h"

/**
 * @brief Check if the magic number is valid
 * @param header The header of the program
 * @return <b>int</b> 1 if the magic number is valid, 0 otherwise
 */
int is_valid_magic(char *header)
{
    int magic = 0;

    for (int index = 1; index < 4; index++)
        magic = magic * 0x100 + ((unsigned char *)header)[index];
    if (magic != COREWAR_EXEC_MAGIC) {
        my_putstr_error("ERROR: Invalid magic number !\n");
        return 0;
    }
    return 1;
}

/**
 * @brief Get the program size
 * @param header The header of the program
 * @return <b>int</b> The program size
 */
int get_prog_size(char *header)
{
    int size = 0;
    char *a = 0;

    for (int index = 8 + PROG_NAME_LENGTH;
    index < 4 + PROG_NAME_LENGTH + 8; index++)
        size = size * 0x100 + ((unsigned char *)header)[index];
    return size;
}
