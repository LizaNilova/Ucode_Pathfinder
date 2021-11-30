#include "../inc/pathfinder.h"

void set_weight_for_islands(int **weights, char **islands, char *s, int waight)
{
    int i = 0; 
    while(islands[i] != NULL)
    {
        if (!mx_strcmp(islands[i], s))
        {
            if ((*weights)[i] < waight && (*weights)[i] > 0) return;
            (*weights)[i] = waight;
            return;
        }
        i++;
    }
}
