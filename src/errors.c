#include "../inc/pathfinder.h"

void mx_print_err(const char *s)
{
    write(2, s, mx_strlen(s));
}

void mx_print_list(t_list *head)
{
    t_list *cur = head;
    while (cur != NULL)
    {
        write(1, cur->data, mx_strlen(cur->data));
        write(1, "\n", 1);
        cur = cur->next;
    }
    write(1, "\n", 1);
}

void command_error(int count_of_arguments)
{
    //ERROR #1
    //command error (no file in command)
    if (count_of_arguments != 2)
    {
        mx_print_err("usage: ./pathfinder [filename]\n");
        exit(0);
    }
}

int file_does_not_exist(char *args[])
{
    //ERROR #2
    //command error (file does not exist)
    int paths = open(args[1], O_RDONLY);
    if (paths < 0)
    {
        mx_print_err("error: file ");
        mx_print_err(args[1]);
        mx_print_err(" does not exist\n");
        exit(0);
    }
    return paths;
}

void errors(int count_of_arguments, char *args[], t_list **islands, t_list **bridges)
{
    command_error(count_of_arguments);
    int paths = file_does_not_exist(args);

    //ERROR #3
    //file error (file is empty)
    char buf;
    int n = read(paths, &buf, 1);
    if (n <= 0)
    {
        mx_print_err("error: file ");
        mx_print_err(args[1]);
        mx_print_err(" is empty\n");
        exit(0);
    }

    //ERROR #4
    //file error (invalid number  of islands - extra symbols)
    if (mx_isdigit(buf))
    {
        while (read(paths, &buf, 1))
        {
            if (!mx_isdigit(buf) && buf != '\n')
            {
                mx_print_err("error: line 1 is not valid\n");
                exit(0);
            }
            if (buf == '\n')
            {
                break;
            }
        }
    }
    else
    {
        mx_print_err("error: line 1 is not valid\n");
        exit(0);
    }
    close(paths);

    //ERROR #5
    //syntaxis error (invalid syntaxis of paths (format))
    int num_of_line = 1, count_of_lines = 1;
    char *paths_str = mx_file_to_str(args[1]);
    for (int i = 0; i < mx_strlen(paths_str); i++)
    {
        if (paths_str[i] == '\n')
        {
            count_of_lines++;
        }
    }

    //extra line ( no \n in the end of file)
    //ERROR #6---------------------------------------
    if (paths_str[mx_strlen(paths_str) - 1] != '\n')
    {
        mx_print_err("error: line ");
        mx_print_err(mx_itoa(count_of_lines));
        mx_print_err(" is not valid\n");
        exit(0);
    }
    //-----------------------------------------------

    int count_dash = 0;
    int count_comma = 0;
    int size_of_bridge = 0;
    int i = 0;
    while (paths_str[i] != '\n')
    {
        i++;
    }
    i++;
    t_list *first_bridge = NULL;
    char *tmp = &paths_str[i];
    t_list *cur_bridge = first_bridge;
    while (paths_str[i + 1] != '\0' && num_of_line < count_of_lines)
    {
        num_of_line++;
        if (paths_str[i - 1] == '\n' && paths_str[i] == '\n')
        {
            mx_print_err("error: line ");
            mx_print_err(mx_itoa(num_of_line));
            mx_print_err(" is not valid\n");
            exit(0);
        }
        count_dash = 0;
        count_comma = 0;
        size_of_bridge = 0;
        tmp = &paths_str[i];

        while (paths_str[i] != '\n' && paths_str[i] != '\0')
        {
            if (num_of_line == 1)
            {
                i++;
                continue;
            }
            if (paths_str[i] == '-')
            {
                count_dash++;
                if (count_dash > 1)
                {
                    mx_print_err("error: line ");
                    mx_print_err(mx_itoa(num_of_line));
                    mx_print_err(" is not valid\n");
                    exit(0);
                }
                if (!mx_isalpha(paths_str[i - 1]) || !mx_isalpha(paths_str[i + 1]))
                {
                    mx_print_err("error: line ");
                    mx_print_err(mx_itoa(num_of_line));
                    mx_print_err(" is not valid\n");
                    exit(0);
                }
            }
            if (paths_str[i] == ',')
            {
                count_comma++;
                if (count_comma > 1 || count_dash == 0)
                {
                    mx_print_err("error: line ");
                    mx_print_err(mx_itoa(num_of_line));
                    mx_print_err(" is not valid\n");
                    exit(0);
                }
            }
            i++;
        }
        if (count_comma == 0 && num_of_line > 1 && num_of_line < count_of_lines)
        {
            mx_printint(count_of_lines);
            mx_print_err("error: line ");
            mx_print_err(mx_itoa(num_of_line));
            mx_print_err(" is not valid\n");
            exit(0);
        }
        if (num_of_line > 1 && num_of_line < count_of_lines)
        {
            mx_push_back(&cur_bridge, tmp);
            if (num_of_line == 2)
            {
                first_bridge = cur_bridge;
            }
        }
        i++;
        if (cur_bridge->next != NULL)
        {
            cur_bridge = cur_bridge->next;
        }
    }

    //ERROR #7
    ///syntaxis error (number of islands not equel number in the first line)
    int first_size = 0, second_size = 0;
    t_list *first_island = NULL;
    t_list *cur_island = first_island;
    cur_bridge = first_bridge;
    for (int k = 0; k < count_of_lines - 2; k++)
    {
        first_size = 0;
        second_size = 0;
        char *temp_bridge = cur_bridge->data;

        while (temp_bridge[first_size] != '-')
        {
            first_size++;
        }
        char *t1 = mx_strnew(first_size);
        mx_strncpy(t1, temp_bridge, first_size);
        while (temp_bridge[first_size + 1 + second_size] != ',')
        {
            second_size++;
        }
        char *t2 = mx_strnew(second_size);
        mx_strncpy(t2, &temp_bridge[first_size + 1], second_size);

        //ПРОВЕРКА НА ПЕТЛЮ
        //---------------------------------
        if (mx_strcmp(t1, t2) == 0)
        {
            mx_print_err("error: line ");
            mx_print_err(mx_itoa(k + 2));
            mx_print_err(" is not valid\n");
            exit(0);
        }
        //---------------------------------

        mx_push_back(&cur_island, t1);
        if (k == 0)
        {
            first_island = cur_island;
        }
        if (cur_island->next != NULL)
            cur_island = cur_island->next;
        mx_push_back(&cur_island, t2);
        if (cur_island->next != NULL)
            cur_island = cur_island->next;
        if (cur_bridge->next != NULL)
        {
            cur_bridge = cur_bridge->next;
        }
    }
    mx_sort_list(first_island, mx_strcmp);

    cur_island = first_island;
    while (cur_island->next != NULL)
    {
        if (cur_island->next->next == NULL)
        {
            if (mx_strcmp(cur_island->data, cur_island->next->data) == 0)
            {
                cur_island->next = NULL;
            }
            break;
        }
        else
        {

            while (mx_strcmp(cur_island->data, cur_island->next->data) == 0 && cur_island->next->next)
            {
                cur_island->next = cur_island->next->next;
            }
            if (cur_island->next->next)
            {
                cur_island = cur_island->next;
            }
        }
    }

    cur_island = first_island;
    int actual_num_of_islands = 0;

    while (cur_island != NULL)
    {
        actual_num_of_islands++;
        cur_island = cur_island->next;
    }
    i = 0;
    while (paths_str[i] != '\n')
    {
        i++;
    }
    char *tmp_num_lines_from_file = mx_strnew(i);
    mx_strncpy(tmp_num_lines_from_file, paths_str, i);
    if (mx_atoi(tmp_num_lines_from_file) != actual_num_of_islands)
    {
        mx_print_err("error: invalid number of islands\n");
        exit(0);
    }

    //ERROR #9
    //duplicate bridges
    cur_bridge = first_bridge;
    while (cur_bridge != NULL)
    {
        char *temp_bridge = cur_bridge->data;
        size_of_bridge = 0;
        while (temp_bridge[size_of_bridge] != '\n')
        {
            size_of_bridge++;
        }
        char *tmp_bridge = mx_strnew(size_of_bridge);
        mx_strncpy(tmp_bridge, temp_bridge, size_of_bridge);
        mx_strcpy(cur_bridge->data, tmp_bridge);

        cur_bridge = cur_bridge->next;
    }

    cur_bridge = first_bridge;
    while (cur_bridge != NULL)
    {
        char *temp_bridge = cur_bridge->data;
        first_size = 0;
        second_size = 0;
        while (temp_bridge[first_size] != '-')
        {
            first_size++;
        }
        char *t1 = mx_strnew(first_size);
        mx_strncpy(t1, temp_bridge, first_size);
        while (temp_bridge[first_size + 1 + second_size] != ',')
        {
            second_size++;
        }
        char *t2 = mx_strnew(second_size);
        mx_strncpy(t2, &temp_bridge[first_size + 1], second_size);

        t_list *cur_bridge_1 = first_bridge;
        while (cur_bridge_1->next != NULL)
        {
            if (mx_strstr(cur_bridge_1->data, t1) != NULL && mx_strstr(cur_bridge_1->data, t2) != NULL && cur_bridge_1 != cur_bridge)
            {
                mx_print_err("error: duplicate bridges\n");
                exit(0);
            }
            cur_bridge_1 = cur_bridge_1->next;
        }
        cur_bridge = cur_bridge->next;
    }

    //ERROR #10
    //value error (sum of lengths between bridges more than INT_MAX value)
    long long actual_sum_of_dists = 0;
    cur_bridge = first_bridge;
    for (int k = 0; k < count_of_lines - 2; k++)
    {
        char *temp_bridge = cur_bridge->data;
        int iter = 0;
        while (temp_bridge[iter] != ',')
        {
            iter++;
        }
        iter++;
        char *pointer_for_begining_of_dist = &temp_bridge[iter];
        int size_of_dist = 0;
        while (temp_bridge[iter] != '\0')
        {
            size_of_dist++;
            iter++;
        }
        char *tmp_dist = mx_strnew(size_of_dist);
        mx_strncpy(tmp_dist, pointer_for_begining_of_dist, size_of_dist);

        actual_sum_of_dists += mx_atoi(tmp_dist);
        if (cur_bridge->next != NULL)
        {
            cur_bridge = cur_bridge->next;
        }
    }
    if (actual_sum_of_dists > 2147483647)
    {
        mx_print_err("error: sum of bridges lengths is too big\n");
        exit(0);
    }

    *islands = first_island;
    *bridges = first_bridge;
}
