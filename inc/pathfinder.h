#ifndef PATHFINDER_H_
#define PATHFINDER_H_

#include "../libmx/inc/libmx.h"

typedef struct s_bridge
{
    int length;
    char *from;
    char *to;
} t_bridge;

void errors(int count_of_arguments, char  *args[], t_list **islands, t_list **bridges);
void mx_print_err(const char *s);
void mx_print_list(t_list *head);
void command_error(int count_of_arguments);
int file_does_not_exist(char *args[]);
t_bridge *parse_bridge(const char *str, int first_size, int second_size);
void finding_paths(t_bridge **bridges, char **nodes, int count_nodes, int count);
void set_weight_for_islands(int **weights, char **nodes, char *s, int waight);
void find_one_of_paths(int *weights, char **nodes, t_bridge **bridges, int count);
void free_bridges(t_bridge ***bridges);
void formating_bridges(t_bridge **bridges, char **islands);
void print_path(int *weights, char **nodes, t_bridge **bridges, int count, char *from, int bridge_count);
int get_path(int *len, int *weights, char **nodes, t_bridge **bridges, int count, char *from, char **path, int *blacklist, int *block, int *permo_block);
int get_weight_of_island(char **islands, int *weights, char *s);
bool is_visited(char **visited, char *s, int visits);
bool unic_island(char *island, char **islands);

#endif
