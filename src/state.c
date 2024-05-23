/*
** EPITECH PROJECT, 2024
** Corewar
** File description:
** The file containing the state functions
*/
/**
 * @file state.c
 * @brief The file containing the state functions
 */

#include "../include/corewar.h"

/**
 * @brief Check if the champions are alive
 * @return <b>void</b>
 */
void check_alive_champions(void)
{
    node_t *trash = NULL;

    for (node_t *tmp = get_corewar()->champions;
    tmp != NULL; tmp = tmp->next) {
        if (((champion_t *)tmp->data)->alive == 0) {
            my_push_front(&trash,
                my_previous_to_next(&get_corewar()->champions, tmp), VOID);
        } else {
            ((champion_t *)tmp->data)->alive = 0;
        }
    }
    my_delete_list(&trash);
}

/**
 * @brief Display the winner
 * @param champions The champions list
 * @return <b>void</b>
 */
void display_winner(node_t *champions)
{
    if (champions == NULL) {
        my_putstr("No winner\n");
        return;
    }
    my_printf("The player %d(%s) has won.\n",
    ((champion_t *)champions->data)->prog_number,
    ((champion_t *)champions->data)->prog_name);
}

/**
 * @brief Check the number of champions
 * @param champions The champions list
 * @return <b>int</b> <u>1</u> if the are more than one champion,
 * <u>0</u> otherwise
 */
int check_champions_number(node_t *champions)
{
    char *first_champion = NULL;

    if (champions == NULL)
        return 0;
    first_champion = ((champion_t *)champions->data)->prog_name;
    for (node_t *tmp = champions->next; tmp != NULL; tmp = tmp->next) {
        if (first_champion != ((champion_t *)tmp->data)->prog_name)
            return 1;
    }
    return 0;
}
