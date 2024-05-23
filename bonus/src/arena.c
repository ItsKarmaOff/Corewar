/*
** EPITECH PROJECT, 2024
** Corewar
** File description:
** The file containing the arena functions
*/
/**
 * @file arena.c
 * @brief The file containing the arena functions
 */

#include "../include/corewar.h"

/**
 * @brief Create the arena
 * @return <b>nodes_t*</b> The arena
 */
node_t *create_arena(void)
{
    node_t *arena = NULL;
    node_t *last_cell = NULL;
    cell_t *cell = NULL;

    for (int index = 0; index < MEM_SIZE; index++) {
        cell = CALLOC(sizeof(cell_t), 1);
        cell->address = index;
        my_push_back(&arena, cell, UNKNOWN);
    }
    for (node_t *tmp = arena; tmp != NULL; tmp = tmp->next)
        last_cell = tmp;
    arena->prev = last_cell;
    last_cell->next = arena;
    return arena;
}

/**
 * @brief Build the arena
 * @return <b>int</b> 0 if an error occurred, 84 otherwise
 */
int build_arena(void)
{
    char *content = NULL;
    node_t *arena = NULL;

    get_corewar()->arena = create_arena();
    for (node_t *tmp = get_corewar()->champions;
    tmp != NULL; tmp = tmp->next) {
        content = read_file(CHAMPION->file_path, CHAMPION->prog_size, 0x890);
        if (content == NULL)
            return 84;
        arena = get_corewar()->arena;
        for (int index = 0; index < CHAMPION->address; index++)
            arena = arena->next;
        for (int index = 0; index < CHAMPION->prog_size; index++) {
            ((cell_t *)arena->data)->value = content[index];
            ((cell_t *)arena->data)->owner = CHAMPION->prog_name;
            arena = arena->next;
        }
    }
    return 0;
}

/**
 * @brief Display the arena
 * @return <b>void</b>
 */
void display_arena(void)
{
    node_t *tmp = get_corewar()->arena;
    int zero = 0;

    for (int i = 0; i < MEM_SIZE;) {
        for (int j = 0; j < 32; j++) {
            zero = ((cell_t *)tmp->data)->value < 0x10 ? my_putstr("0") : zero;
            my_putnbr_base(((cell_t *)tmp->data)->value, "0123456789ABCDEF");
            tmp = tmp->next;
            i++;
        }
        my_putchar('\n');
    }
}

/**
 * @brief Get the arena node from an address
 * @param address The address of the node
 * @return <b>node_t*</b> The arena
 */
node_t *get_arena_node(int address)
{
    node_t *arena = get_corewar()->arena;

    for (int index = 0; index < address; index++)
        arena = arena->next;
    return arena;
}
