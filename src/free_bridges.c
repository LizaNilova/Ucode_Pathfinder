#include "../inc/pathfinder.h"

void free_bridges(t_bridge ***bridges)
{
    for (int i = 0; (*bridges)[i] != NULL; i++)
    {
        mx_strdel(&(*bridges)[i]->from);
        mx_strdel(&(*bridges)[i]->to);
        free((*bridges)[i]);
    }
    *bridges = NULL;
}
