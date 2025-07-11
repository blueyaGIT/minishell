#include "minishell.h"

char *read_line(const char *prompt)
{
    char *line = readline(prompt);
    if (line && *line)
        add_history(line);
    return (line);
}