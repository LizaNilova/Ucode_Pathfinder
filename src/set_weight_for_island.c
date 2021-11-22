#include "../inc/pathfinder.h"

void set_weight_for_islands(int **weights, char **islands, char *s, int waight)
{
    for (int i = 0; islands[i] != NULL; i++)
    {
        if (!mx_strcmp(islands[i], s))
        {
            if ((*weights)[i] < waight && (*weights)[i] > 0) return;
            (*weights)[i] = waight;
            return;
        }
    }
}
