#include "../inc/pathfinder.h"

void find_one_of_paths(int *weights, char **islands, t_bridge **bridges, int count_of_islands)
{
    char **visited = malloc(count_of_islands * sizeof *visited);
    char *cur;
    int visits = 0;
    int min = 0;
    int weight = 0;
    for (int i = 0; i < count_of_islands; i++)
    {
        min = 0;
        while (is_visited(visited, islands[min], visits)) min++;
        if (visits == count_of_islands) break;
        for (int j = 0; j < count_of_islands; j++)
        {
            if (is_visited(visited, islands[j], visits)) continue;
            if (weights[j] >= 0 && (weights[min] < 0 || weights[min] > weights[j]))
            {
                min = j;
            }
        }
        cur = islands[min];
        for (int j = 0; bridges[j] != NULL; j++)
        {
            if (!mx_strcmp(bridges[j]->from, cur))
            {
                if (is_visited(visited, bridges[j]->to, visits)) continue;
                weight = get_weight_of_island(islands, weights, cur);
                set_weight_for_islands(&weights, islands, bridges[j]->to, weight + bridges[j]->length);
            }
            else if (!mx_strcmp(bridges[j]->to, cur))
            {
                if (is_visited(visited, bridges[j]->from, visits)) continue;
                weight = get_weight_of_island(islands, weights, cur);
                set_weight_for_islands(&weights, islands, bridges[j]->from, weight + bridges[j]->length);
            }
        }
        visited[visits] = cur;
        visits++;
    }
    free(visited);
}
