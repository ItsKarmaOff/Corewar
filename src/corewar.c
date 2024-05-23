/*
** EPITECH PROJECT, 2024
** Corewar
** File description:
** The file containing the corewar functions
*/
/**
 * @file corewar.c
 * @brief The file containing the corewar functions
 */

#include "../include/corewar.h"

/**
 * @brief Get the corewar structure
 * @return <b>corewar_t*</b> The corewar structure
 */
corewar_t *get_corewar(void)
{
    static corewar_t corewar = {0};
    static int start = 1;

    if (start) {
        corewar.total_cycle = 1;
        corewar.nbr_cycle = CYCLE_TO_DIE;
        start = 0;
    }
    return &corewar;
}

/**
 * @brief Free the corewar structure and all the memory allocated
 * @return <b>void</b>
 */
void free_corewar(void)
{
    corewar_t *corewar = get_corewar();

    if (corewar == NULL)
        return;
    if (corewar->champions != NULL)
        my_delete_list(&corewar->champions);
    if (corewar->arena != NULL)
        my_delete_circle_list(&corewar->arena);
    my_free();
}

/**
 * @brief The virtual machine of the corewar
 * @return <b>int</b> <u>0</u> if the corewar is running, <u>84</u> otherwise
 */
int corewar(void)
{
    corewar_t *corewar = get_corewar();

    while (check_champions_number(corewar->champions)) {
        if (corewar->dump_cycle != 0 &&
        corewar->total_cycle % corewar->dump_cycle == 0)
            display_arena();
        if (corewar->total_cycle % corewar->nbr_cycle == 0)
            check_alive_champions();
        for (node_t *tmp = corewar->champions; tmp != NULL; tmp = tmp->next)
            execute_instructions((champion_t *)tmp->data);
        corewar->total_cycle = (corewar->total_cycle + 1 > corewar->nbr_cycle)
            ? 1 : corewar->total_cycle + 1;
    }
    display_winner(corewar->champions);
    return 0;
}
