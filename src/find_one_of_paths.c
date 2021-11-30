#include "../inc/pathfinder.h"

void find_one_of_paths(int *weights, char **islands, t_bridge **bridges, int count_of_islands)
{
    char **visited = malloc(count_of_islands * sizeof *visited);
    char *cur;
    int visits = 0;
    int min = 0;
    int weight = 0;
    int i = 0;
    while (i < count_of_islands)
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
        int j = 0;
        while(bridges[j] != NULL)
        {
            if (!mx_strcmp(bridges[j]->from, cur))
            {
                if (is_visited(visited, bridges[j]->to, visits)){
                    j++;
                    continue;
                } 
                weight = get_weight_of_island(islands, weights, cur);
                set_weight_for_islands(&weights, islands, bridges[j]->to, weight + bridges[j]->length);
            }
            else if (!mx_strcmp(bridges[j]->to, cur))
            {
                if (is_visited(visited, bridges[j]->from, visits)){
                    j++;
                    continue;
                } 
                weight = get_weight_of_island(islands, weights, cur);
                set_weight_for_islands(&weights, islands, bridges[j]->from, weight + bridges[j]->length);
            }
            j++;
        }
        visited[visits] = cur;
        visits++;
        i++;
    }
    free(visited);
}
