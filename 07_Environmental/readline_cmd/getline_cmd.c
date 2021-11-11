#include <stdio.h>
#include <unistd.h>
#include <readline/readline.h>

unsigned getline_cmd(char **cmd_line) 
{
    char *prompt;
    if (isatty(fileno(stdin)))
        prompt = "Command: ";
    else
        prompt = "";

    *cmd_line = readline(prompt);
    if (*cmd_line == NULL) 
        return EOF;

    return strlen(*cmd_line);
}