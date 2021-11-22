#include "../inc/pathfinder.h"

int get_weight_of_island(char **islands, int *weights, char *s)
{
    for (int i = 0; islands[i] != NULL; i++)
    {
        if (!mx_strcmp(islands[i], s)) return weights[i];
    }
    return 0;
}
