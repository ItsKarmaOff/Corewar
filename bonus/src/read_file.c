/*
** EPITECH PROJECT, 2024
** Corewar
** File description:
** The file containing the functions for reading a file
*/
/**
 * @file read_file.c
 * @brief The file containing the functions for reading a file
 */

#include "../include/corewar.h"

/**
 * @brief Read a file and return the content
 * @param filepath The file path
 * @param size The size of the bytes to read
 * @param start The start of the reading
 * @return <b>char*</b> The content of the file or NULL if an error occurred
 */
char *read_file(char *filepath, int size, int start)
{
    FILE *file = fopen(filepath, "r");
    char *buffer = NULL;

    if (file == NULL) {
        my_putstr_error("ERROR: Can't open the file !\n");
        return NULL;
    }
    buffer = CALLOC(size + 1, sizeof(char));
    if (buffer == NULL)
        return NULL;
    fseek(file, start, SEEK_SET);
    if (fread(buffer, 1, size, file) != (size_t)size) {
        my_putstr_error("ERROR: Can't read the file !\n");
        return NULL;
    }
    buffer[size] = '\0';
    fclose(file);
    return buffer;
}
