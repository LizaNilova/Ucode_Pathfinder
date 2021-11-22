#include "../inc/pathfinder.h"

int get_path(int *length, int *weights, char **islands, t_bridge **bridges, int count, char *from, char **path, int *blacklist, int *block, int *permo_block)
{
    int clength = 0;
    int cweight = -1;
    int from_weight = 0;
    int steps = 1;
    char *cisland = from;
    int prev_bridge_i = -1;
    path[0] = from;
    int needed_bridge = -1;
    bool flag = true;
    bool f = true;
    for (int j = 0; j < count + 1 && flag; j++)
    {
        f = true;
        from_weight = get_weight_of_island(islands, weights, from);
        for (int i = 0; bridges[i] != NULL; i++)
        {
            if (blacklisted(i, blacklist, *block)) continue;
            if (!mx_strcmp(bridges[i]->from, from))
            {
                cisland = bridges[i]->to;
                cweight = get_weight_of_island(islands, weights, bridges[i]->to);
                clength = bridges[i]->length;
            }
            else if (!mx_strcmp(bridges[i]->to, from))
            {
                cisland = bridges[i]->from;
                cweight = get_weight_of_island(islands, weights, bridges[i]->from);
                clength = bridges[i]->length;
            }
            else continue;
            if (from_weight < clength) continue;
            if (cweight == 0)
            {
                blacklist[*block] = i;
                *block += 1;
                path[steps] = cisland;
                length[steps - 1] = clength;
                steps++;
                flag = false;
                f = false;
                needed_bridge = i;
                break;
            }
            if (from_weight - clength == cweight)
            {
                prev_bridge_i = i;
                length[steps - 1] = clength;
                from = cisland;
                path[steps] = from;
                steps++;
                f = false;
                break;
            }
        }
        if (f)
        {
            if (!mx_strcmp(from, path[0]))
            {
                return -1;
            }
            j = 0;
            from = path[0];
            steps = 1;
            blacklist[*block] = prev_bridge_i;
            *block += 1;
            if (!mx_strcmp(bridges[prev_bridge_i]->from, path[0])
                || !mx_strcmp(bridges[prev_bridge_i]->to, path[0]))
            {
                blacklist[*permo_block] = prev_bridge_i;
                *permo_block += 1;
                *block = *permo_block;
            }
        }
        if (!flag && (!mx_strcmp(bridges[needed_bridge]->from, path[0])
            || !mx_strcmp(bridges[needed_bridge]->to, path[0])))
        {
            blacklist[*permo_block] = needed_bridge;
            *permo_block += 1;
            *block = *permo_block;
        }
    }
    path[steps] = NULL;
    return steps;
}
