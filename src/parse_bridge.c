#include "../inc/pathfinder.h"

t_bridge *parse_bridge(const char *str, int first_size, int second_size)
{
    t_bridge *bridge = malloc(sizeof(*bridge));
    char **slice = malloc(sizeof(char **) * (mx_strlen(str)));
    slice = mx_strsplit(str, ',');
    bridge->length = mx_atoi(slice[1]);
    char **names = malloc(sizeof(char **) * (first_size + second_size));
    names = mx_strsplit(slice[0], '-');        
    bridge->from = mx_strdup(names[0]);
    bridge->to = mx_strdup(names[1]);
    mx_del_strarr(&names);
    mx_del_strarr(&slice);
    return bridge;
}
