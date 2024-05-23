/*
** EPITECH PROJECT, 2024
** Corewar
** File description:
** The file containing the parsing functions
*/
/**
 * @file parsing.c
 * @brief The file containing the parsing functions
 */

#include "../include/corewar.h"

/**
 * @brief Check the dump flag
 * @param index The index of the current argument
 * @param argv The arguments
 * @return <b>int</b> <u>1</u> if the check is a success,
 * <u>84</u> if an error occurred and <u>0</u> otherwise
 */
static int check_dump(int *index, char **argv)
{
    if (my_strcmp(argv[*index], "-dump") == 0
    || my_strcmp(argv[*index], "-d") == 0) {
        if (get_corewar()->dump_cycle != 0) {
            return my_putstr_error("ERROR: Dump already set !\n");
        }
        get_corewar()->dump_cycle =
            my_super_number(argv[*index + 1], (NB) {0, 0, 0, 0});
        if (my_errno || get_corewar()->dump_cycle <= 0) {
            return my_putstr_error("ERROR: Invalid dump cycle !\n");
        }
        *index += 1;
        return 1;
    }
    return 0;
}

/**
 * @brief Check the champion flags
 * @param index The index of the current argument
 * @param argc The number of arguments
 * @param argv The arguments
 * @param type The type of the flag
 * @return <b>int</b> The champion number or address
 * or <u>-84</u> if an error occurred
 */
static int check_champion_flags(int *index, int argc, char **argv, int type)
{
    int number = 0;

    if (type == 0 && my_strcmp(argv[*index], "-n") == 0) {
        number = my_super_number(argv[*index + 1], (NB) {0, 0, 0, 0});
        if (my_errno || number <= 0)
            return -my_putstr_error("ERROR: Invalid champion number !\n");
        *index += 2;
        return number;
    }
    if (type && my_strcmp(argv[*index], "-a") == 0) {
        number = my_super_number(argv[*index + 1], (NB) {0, 0, 0, 0});
        if (my_errno || number < 0 || number >= MEM_SIZE)
            return -my_putstr_error("ERROR: Invalid champion address !\n");
        *index += 2;
        return number;
    }
    return -1;
}

/**
 * @brief Check the champion and add it to the corewar structure
 * @param index The index of the current argument
 * @param argc The number of arguments
 * @param argv The arguments
 * @return <b>int</b> <u>0</u> if the check is a success, <u>84</u> otherwise
 */
static int check_champion(int *index, int argc, char **argv)
{
    int number = check_champion_flags(index, argc, argv, 0);
    int address = check_champion_flags(index, argc, argv, 1);
    champion_t *champion = NULL;

    if (number == -1)
        number = check_champion_flags(index, argc, argv, 0);
    if (champion_number_exist(number))
        return my_putstr_error("ERROR: Double champion number !\n");
    if (number == -84 || address == -84)
        return 84;
    if (number == -1)
        number = get_next_champion_number();
    champion = CALLOC(1, sizeof(champion_t));
    champion->prog_number = number;
    champion->address = address;
    champion->file_path = argv[*index];
    my_push_back(&get_corewar()->champions, champion, UNKNOWN);
    return 0;
}

/**
 * @brief Parse the arguments
 * @param argc The number of arguments
 * @param argv The arguments
 * @return <b>int</b> <u>0</u> if the parsing is a success, <u>84</u> otherwise
 */
int parse_args(int argc, char **argv)
{
    corewar_t *corewar = get_corewar();
    int status = 0;

    for (int index = 1; index < argc; index++) {
        status = check_dump(&index, argv);
        if (status == 84)
            return 84;
        if (status == 1)
            continue;
        status = check_champion(&index, argc, argv);
        if (status == 0)
            continue;
        return 84;
    }
    if (my_list_size(corewar->champions) < 2 ||
    my_list_size(corewar->champions) > MAX_ARGS_NUMBER)
        return my_putstr_error("ERROR: Invalid number of champions !\n");
    return analyse_champions();
}
