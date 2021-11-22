#include "../inc/pathfinder.h"

bool unic_island(char *island, char **islands)
{
    int i = 0;
    while (islands[i])
    {
        if (mx_strcmp(island, islands[i]) == 0)
        {
            return false;
        }
        i++;
    }
    return true;
}

int main(int argc, char *argv[])
{
    t_list *islands_unic = NULL;
    t_list *bridges_unic = NULL;
    errors(argc, argv, &islands_unic, &bridges_unic);
    t_list *cur_island = islands_unic;
    t_list *cur_bridge_str = bridges_unic;
    int n = 0;

    while (cur_island != NULL)
    {
        n++;
        cur_island = cur_island->next;
    }
    char **islands = malloc((n + 1) * sizeof(char **));
    islands[n] = NULL;

    int i = 0;
    int count_of_bridges = 0;
    while (cur_bridge_str != NULL)
    {
        count_of_bridges++;
        cur_bridge_str = cur_bridge_str->next;
    }

    t_bridge **bridges = malloc((count_of_bridges + 1) * sizeof(t_bridge));
    bridges[count_of_bridges] = NULL;
    i = 0;
    int j = 0;
    char *temp_bridge = NULL;
    int first_size = 0;
    int second_size = 0;
    cur_bridge_str = bridges_unic;

    while (cur_bridge_str != NULL)
    {
        first_size = 0;
        second_size = 0;
        temp_bridge = cur_bridge_str->data;

        while (temp_bridge[first_size] != '-')
        {
            first_size++;
        }
        char *t1 = mx_strnew(first_size);
        mx_strncpy(t1, temp_bridge, first_size);
        if (unic_island(t1, islands))
        {
            islands[j] = t1;
            j++;
        }
        while (temp_bridge[first_size + 1 + second_size] != ',')
        {
            second_size++;
        }
        char *t2 = mx_strnew(second_size);
        mx_strncpy(t2, &temp_bridge[first_size + 1], second_size);
        if (unic_island(t2, islands))
        {
            islands[j] = t2;
            j++;
        }
        bridges[i] = parse_bridge(cur_bridge_str->data, first_size, second_size);
        i++;
        cur_bridge_str = cur_bridge_str->next;
    }

    finding_paths(bridges, islands, n, count_of_bridges);
}
