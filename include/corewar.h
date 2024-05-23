/*
** EPITECH PROJECT, 2024
** Corewar
** File description:
** The header of the corewar project
*/
/**
 * @file corewar.h
 * @brief The header of the corewar project
 */

#include "mymemory.h"
#include "myop.h"
#include "ncurses.h"

#ifndef COREWAR_H_
    #define COREWAR_H_

// MACROS :

    #define CHAMPION ((champion_t *)tmp->data)



// STRUCTURES :

/**
 * @brief The cell structure
 * @note A cell is a memory case of the arena
 */
typedef struct cell_s {
    int address; // The address of the cell
    unsigned char value; // The value of the cell
    char *owner; // The last champion who wrote in the cell
} cell_t;

/**
 * @brief The champion structure
 */
typedef struct champion_s {
    char *file_path; // The path of the file of the champion
    char *prog_name; // The program name
    char *comment; // The comment of the program
    int prog_size; // The program size
    int prog_number; // The program number
    int address; // The address of the program in the arena
    int reg[REG_NUMBER]; // The registers of the program
    int cooldown; // The cooldown of the program
    bool alive; // The alive status of the program
    int program_counter; // The next instruction to execute
    bool carry; // The carry of the program
} champion_t;

/**
 * @brief The corewar structure
 */
typedef struct corewar_s {
    int nbr_cycle; // The number of cycle to die
    int nbr_live; // The number of live done
    int total_cycle; // The total of cycle done
    int dump_cycle; // The cycle number to dump the memory
    node_t *champions; // The champions list
    champion_t *initial_champion[5]; // The initial champion
    node_t *arena; // The arena
} corewar_t;



// FUNCTIONS PROTOTYPES :

    // Corewar functions :

/**
* @brief Get the corewar structure
* @return <b>corewar_t*</b> The corewar structure
*/
corewar_t *get_corewar(void);

/**
 * @brief Free the corewar structure and all the memory allocated
 * @return <b>void</b>
 */
void free_corewar(void);

/**
 * @brief The virtual machine of the corewar
 * @return <b>int</b> <u>0</u> if the corewar is running, <u>84</u> otherwise
 */
int corewar(void);


    // Parsing functions :

/**
* @brief Parse the arguments
* @param argc The number of arguments
* @param argv The arguments
* @return <b>int</b> <u>0</u> if the parsing is a success, <u>84</u> otherwise
*/
int parse_args(int argc, char **argv);


    // Champion functions :

/**
* @brief Get the next champion number disponible
* @return <b>int</b> The next champion number
*/
int get_next_champion_number(void);

/**
 * @brief Check if a champion number exist
 * @param number The champion number
 * @return <b>int</b> 1 if the champion number exist, 0 otherwise
 */
int champion_number_exist(int number);

/**
 * @brief Analyse each champion files and complete the champion structure
 * @return <b>int</b> <u>0</u> if the analyse is a success, <u>84</u> otherwise
 */
int analyse_champions(void);

/**
 * @brief Get a champion by its number
 * @param number The champion number
 * @return <b>champion_t*</b> The champion
 */
champion_t *get_champion_by_number(int number);


    // Update functions :

/**
* @brief Update the program counter of a champion
* @param champion The champion to update
* @param value The value to add to the program counter
* @return <b>void</b>
*/
void update_program_counter(champion_t *champion, int value);

/**
 * @brief Update the carry of a champion
 * @param champion The champion to update
 * @param value The value to check
 * @return <b>void</b>
 */
void update_carry(champion_t *champion, int value);


    // Read files functions :

/**
 * @brief Read a file and return the content
 * @param filepath The file path
 * @param size The size of the bytes to read
 * @param start The start of the reading
 * @return <b>char*</b> The content of the file or NULL if an error occurred
 */
char *read_file(char *filepath, int size, int start);


    // Header functions :

/**
 * @brief Get the program size
 * @param header The header of the program
 * @return <b>int</b> The program size
 */
int get_prog_size(char *header);

/**
 * @brief Check if the magic number is valid
 * @param header The header of the program
 * @return <b>int</b> 1 if the magic number is valid, 0 otherwise
 */
int is_valid_magic(char *header);


    // Arena functions :

/**
 * @brief Build the arena
 * @return <b>int</b> 0 if an error occurred, 84 otherwise
 */
int build_arena(void);

/**
* @brief Display the arena
* @return <b>void</b>
*/
void display_arena(void);

/**
 * @brief Get the arena node from an address
 * @param address The address of the node
 * @return <b>node_t*</b> The arena
 */
node_t *get_arena_node(int address);


    // State functions :

/**
* @brief Check if the champions are alive
* @return <b>void</b>
*/
void check_alive_champions(void);

/**
* @brief Display the winner
* @param champions The champions list
* @return <b>void</b>
*/
void display_winner(node_t *champions);

/**
 * @brief Check the number of champions
 * @param champions The champions list
 * @return <b>int</b> <u>1</u> if the are more than one champion,
 * <u>0</u> otherwise
 */
int check_champions_number(node_t *champions);


    // Instructions functions :

/**
* @brief Execute the instructions
* @param champion The champion to execute the instructions
* @return <b>void</b>
*/
void execute_instructions(champion_t *champion);

/**
 * @brief Get int from address
 * @param address The address to get the int
 * @param size The size of the int
 * @return <b>int</b> The int
 */
int get_int_from_address(node_t *address, int size);

/**
 * @brief Write int in address
 * @param champion The champion to write the int
 * @param address The address to write the int
 * @param value The value to write
 */
void write_int_in_address(champion_t *champion, node_t *address, int value);

/**
 * @brief Read int in address
 * @param address The address to read the int
 * @param size The size of the int
 * @return <b>int</b> The int read
 */
int read_int_in_address(node_t *address, int size);


    // Coding byte functions :

/**
 * @brief Get the type of byte with the coding byte at the index
 * @param coding_byte The coding byte to get the index
 * @param index The index of the coding byte value
 * @return <b>char</b> The type of byte
 */
char get_code_byte_index(char coding_byte, int index);

/**
 * @brief Get the size of the type
 * @param type The type to get the size
 * @param max_size The max size of the type
 * @return <b>char</b> The size of the type
 */
char get_size_from_type(char type, bool max_size);

/**
 * @brief Get the size of the coding byte
 * @param coding_byte The coding byte to get the size
 * @param max_size The max size of the coding byte
 * @return <b>char</b> The size of the coding byte
 */
char get_size_of_coding_byte(char coding_byte, bool max_size);


    // All instructions functions :

/**
 * @brief The add function
 * @param champion The champion to execute the add function
 * @param address The address of the add function
 * @return <b>void</b>
 */
void exec_add(champion_t *champion, node_t *address);

/**
 * @brief The aff function
 * @param champion The champion to execute the aff function
 * @param address The address of the aff function
 * @return <b>void</b>
 */
void exec_aff(champion_t *champion, node_t *address);

/**
 * @brief The and function
 * @param champion The champion to execute the and function
 * @param address The address of the and function
 * @return <b>void</b>
 */
void exec_and(champion_t *champion, node_t *address);

/**
 * @brief The fork function
 * @param champion The champion to execute the fork function
 * @param address The address of the fork function
 * @return <b>void</b>
 */
void exec_fork(champion_t *champion, node_t *address);

/**
 * @brief The ld function
 * @param champion The champion to execute the ld function
 * @param address The address of the ld function
 * @return <b>void</b>
 */
void exec_ld(champion_t *champion, node_t *address);

/**
 * @brief The ldi function
 * @param champion The champion to execute the ldi function
 * @param address The address of the ldi function
 * @return <b>void</b>
 */
void exec_ldi(champion_t *champion, node_t *address);

/**
 * @brief The lfork function
 * @param champion The champion to execute the lfork function
 * @param address The address of the lfork function
 * @return <b>void</b>
 */
void exec_lfork(champion_t *champion, node_t *address);

/**
 * @brief The live function
 * @param champion The champion to execute the live function
 * @param address The address of the live function
 * @return <b>void</b>
 */
void exec_live(champion_t *champion, node_t *address);

/**
 * @brief The lld function
 * @param champion The champion to execute the lld function
 * @param address The address of the lld function
 * @return <b>void</b>
 */
void exec_lld(champion_t *champion, node_t *address);

/**
 * @brief The lldi function
 * @param champion The champion to execute the lldi function
 * @param address The address of the lldi function
 * @return <b>void</b>
 */
void exec_lldi(champion_t *champion, node_t *address);

/**
 * @brief The or function
 * @param champion The champion to execute the or function
 * @param address The address of the or function
 * @return <b>void</b>
 */
void exec_or(champion_t *champion, node_t *address);

/**
 * @brief The st function
 * @param champion The champion to execute the st function
 * @param address The address of the st function
 * @return <b>void</b>
 */
void exec_st(champion_t *champion, node_t *address);

/**
 * @brief The sti function
 * @param champion The champion to execute the sti function
 * @param address The address of the sti function
 * @return <b>void</b>
 */
void exec_sti(champion_t *champion, node_t *address);

/**
 * @brief The sub function
 * @param champion The champion to execute the sub function
 * @param address The address of the sub function
 * @return <b>void</b>
 */
void exec_sub(champion_t *champion, node_t *address);

/**
 * @brief The xor function
 * @param champion The champion to execute the xor function
 * @param address The address of the xor function
 * @return <b>void</b>
 */
void exec_xor(champion_t *champion, node_t *address);

/**
 * @brief The zjmp function
 * @param champion The champion to execute the zjmp function
 * @param address The address of the zjmp function
 * @return <b>void</b>
 */
void exec_zjmp(champion_t *champion, node_t *address);



#endif /* COREWAR_H_ */
