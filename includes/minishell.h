#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

typedef struct s_node
{
	char *args;
	char **filename;
	char **redirections;
} t_node;

typedef struct s_mini
{
	char *input;
	t_node node;
} t_mini;