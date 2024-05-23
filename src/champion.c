/*
** EPITECH PROJECT, 2024
** Corewar
** File description:
** The file containing the champion functions
*/
/**
 * @file champion.c
 * @brief The file containing the champion functions
 */

#include "../include/corewar.h"

/**
 * @brief Get the next champion number disponible
 * @return <b>int</b> The next champion number
 */
int get_next_champion_number(void)
{
    corewar_t *corewar = get_corewar();
    int number = 1;
    int found = 0;

    for (; number < MAX_INT
    && get_corewar()->champions != NULL; number++) {
        found = 0;
        for (node_t *tmp = corewar->champions; tmp != NULL; tmp = tmp->next)
            found =
                (((champion_t *)tmp->data)->prog_number == number) ? 1 : found;
        if (found == 0)
            break;
    }
    return number;
}

/**
 * @brief Check if a champion number exist
 * @param number The champion number
 * @return <b>int</b> 1 if the champion number exist, 0 otherwise
 */
int champion_number_exist(int number)
{
    corewar_t *corewar = get_corewar();

    for (node_t *tmp = corewar->champions; tmp != NULL; tmp = tmp->next) {
        if (((champion_t *)tmp->data)->prog_number == number)
            return 1;
    }
    return 0;
}

/**
 * @brief Set the champion parameters
 * @param champion The champion to set the parameters
 * @param header The header of the champion
 * @return <b>void</b>
 */
static void set_champion_params(champion_t *champion, char *header)
{
    champion->prog_name = my_malloc_strndup(header + 4, PROG_NAME_LENGTH);
    champion->prog_size = get_prog_size(header);
    champion->comment = my_malloc_strndup(header + 140, COMMENT_LENGTH);
    champion->reg[0] = champion->prog_number;
    champion->program_counter = champion->address;
    champion->carry = true;
}

/**
 * @brief Analyse each champion files and complete the champion structure
 * @return <b>int</b> <u>0</u> if the analyse is a success, <u>84</u> otherwise
 */
int analyse_champions(void)
{
    corewar_t *corewar = get_corewar();
    champion_t *champion = NULL;
    int size = MEM_SIZE / my_list_size(corewar->champions);
    int number = 0;
    char *header = NULL;

    for (node_t *tmp = corewar->champions; tmp != NULL; tmp = tmp->next) {
        champion = (champion_t *)tmp->data;
        if (champion->address == -1)
            champion->address = size * number;
        header = read_file(champion->file_path, sizeof(header_t), 0);
        if (header == NULL || is_valid_magic(header) == 0)
            return 84;
        set_champion_params(champion, header);
        corewar->initial_champion[number] = champion;
        number++;
    }
    return 0;
}

/**
 * @brief Get a champion by its number
 * @param number The champion number
 * @return <b>champion_t*</b> The champion
 */
champion_t *get_champion_by_number(int number)
{
    corewar_t *corewar = get_corewar();

    for (node_t *tmp = corewar->champions; tmp != NULL; tmp = tmp->next) {
        if (((champion_t *)tmp->data)->prog_number == number)
            return (champion_t *)tmp->data;
    }
    return NULL;
}
