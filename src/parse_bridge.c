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

    char **dst = names;
	while (*dst) {
		mx_strdel(dst++);
	}
	free(names);
    names = NULL;
    //mx_del_strarr(&names);

    dst = slice;
	while (*dst) {
		mx_strdel(dst++);
	}
	free(slice);
    slice = NULL;

    //mx_del_strarr(&slice);
    return bridge;
}
