/*
** EPITECH PROJECT, 2023
** Corewar
** File description:
** The main file of the project
*/
/**
 * @file main.c
 * @brief The main file of the project
 */

#include "../include/corewar.h"

/**
 * @brief Display the help
 * @return <b>void</b>
 */
static void display_help(void)
{
    my_fprintf(2, "USAGE\n\t./corewar [-dump nbr_cycle] [[-n prog_number]"
        "[-a load_address] prog_name] ...\n\nDESCRIPTION\n\t-dump\tnbr_cycle"
        " dumps the memory after the nbr_cycle execution (if the round isn't"
        " already over) with the following format: 32 bytes/line in"
        " hexadecimal (A0BCDEFE1DD3...)\n\t-n\tprog_number sets the next"
        " program's number. By default, the first free number in the parameter"
        " order\n\t-a\tload_address sets the next program's loading address."
        " When no address is specified, optimize the addresses so that the"
        " processes are as far away from each other as possible."
        " The addresses are MEM_SIZE modulo\n");
}

/**
 * @brief The main function of the project
 * @param argc The number of arguments
 * @param argv The arguments
 * @return <b>int</b> <u>0</u> if the program ended successfully,
 * <u>84</u> otherwise
 */
int main(int argc, char **argv)
{
    int result = 0;

    if (argc < 2) {
        display_help();
        return 84;
    }
    if (my_strcmp(argv[1], "-h") == 0 || my_strcmp(argv[1], "--help") == 0) {
        display_help();
        return 0;
    }
    if (parse_args(argc, argv) || build_arena()) {
        free_corewar();
        return 84;
    }
    result = corewar();
    free_corewar();
    return result;
}
