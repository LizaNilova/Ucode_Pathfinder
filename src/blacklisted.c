#include "../inc/pathfinder.h"

bool blacklisted(int c, int *blacklist, int size)
{
    for (int i = 0; i < size; i++)
    {
        if (blacklist[i] == c) return true;
    }
    return false;
}
