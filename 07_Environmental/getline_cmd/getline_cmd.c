#include <stdio.h>

unsigned getline_cmd(char **cmd_line)
{
    size_t n;
    return getline(cmd_line, &n, stdin);
}