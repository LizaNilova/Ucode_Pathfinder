#include "../inc/pathfinder.h"

int get_island_index(char **islands, char *island)
{
    int i = 0;
    while (islands[i] != NULL)
    {
        if (!mx_strcmp(islands[i], island))
            return i;
        i++;
    }
    return -1;
}

void formating_bridges(t_bridge **bridges, char **islands)
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
}
