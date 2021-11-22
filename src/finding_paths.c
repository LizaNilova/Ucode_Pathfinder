#include "../inc/pathfinder.h"

int get_island_index(char **islands, char *island)
{
    int i = 0;
    while(islands[i] != NULL)
    {
        if (!mx_strcmp(islands[i], island)) return i;
        i++;
    }
    return -1;
}


void finding_paths(t_bridge **bridges, char **islands, int count_islands, int count)
{
    t_bridge *buf;

    for (int i = 0; bridges[i] != NULL; i++)
    {
        for (int j = i + 1; bridges[j] != NULL; j++)
        {
            if (get_island_index(islands, bridges[i]->from) +
                get_island_index(islands, bridges[i]->to) >
                get_island_index(islands, bridges[j]->from) +
                get_island_index(islands, bridges[j]->to))
            {
                buf = bridges[i];
                bridges[i] = bridges[j];
                bridges[j] = buf;
            }
        }
    }

    int *weights_of_islands = malloc((count_islands + 1) * sizeof(int));
    for (int i = 0; i < count_islands - 1; i++)
    {
        for (int j = i + 1; j < count_islands; j++)
        {
            for (int k = 0; k < count_islands; k++) weights_of_islands[k] = -1;
            set_weight_for_islands(&weights_of_islands, islands, islands[j], 0);
            find_one_of_paths(weights_of_islands, islands, bridges, count_islands);
            print_path(weights_of_islands, islands, bridges, count_islands, islands[i], count);
        }
    }

    free_bridges(&bridges);
    mx_del_strarr(&islands);
}
