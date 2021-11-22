#include "../inc/pathfinder.h"

void print_path(int *weights, char **islands, t_bridge **bridges, int count_of_islands, char *from, int bridge_count)
{
    int *dist = malloc(count_of_islands * sizeof *dist);
    char **path = malloc((count_of_islands + 1) * sizeof *path);
    path[count_of_islands] = NULL;
    int *blacklist = malloc(bridge_count * sizeof *blacklist);
    int perm_blocked = 0;
    int steps = 0;
    int blocked = 0;
    while (true)
    {
        steps = get_path(dist, weights, islands, bridges, count_of_islands, from, path, blacklist, &blocked, &perm_blocked);
        if (steps == -1) break;

        for (int i = 0; i < 40; i++) mx_printchar('=');
        mx_printchar('\n');

        mx_printstr("Path: ");
        mx_printstr(path[0]);
        mx_printstr(" -> ");
        mx_printstr(path[steps - 1]);
        mx_printchar('\n');
        mx_printstr("Route: ");
        mx_print_strarr(path, " -> ");
        mx_printstr("Distance: ");
        int sum = 0;
        for (int i = 0; i < steps - 1; i++)
        {
            sum += dist[i];
            mx_printint(dist[i]);
            if (i + 1 != steps - 1) mx_printstr(" + ");
        }
        if (sum != dist[0])
        {
            mx_printstr(" = ");
            mx_printint(sum);
        }
        mx_printchar('\n');
        for (int i = 0; i < 40; i++) mx_printchar('=');
        mx_printchar('\n');
    }
    free(dist);
    free(path);
    free(blacklist);
}
