#include "../inc/pathfinder.h"

void finding_paths(t_bridge **bridges, char **islands, int count_islands, int count)
{
    formating_bridges(bridges, islands);
    int *weights_of_islands = malloc((count_islands + 1) * sizeof(int));
    for (int i = 0; i < count_islands - 1; i++)
    {
        for (int j = i + 1; j < count_islands; j++)
        {
            for (int k = 0; k < count_islands; k++)
                weights_of_islands[k] = -1;
            set_weight_for_islands(&weights_of_islands, islands, islands[j], 0);
            find_one_of_paths(weights_of_islands, islands, bridges, count_islands);
            print_path(weights_of_islands, islands, bridges, count_islands, islands[i], count);
        }
    }

    free_bridges(&bridges);
    mx_del_strarr(&islands);
}
