#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include "libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_node
{
	char *args;
	char **filename;
	char **redirections;
} t_node;

typedef struct s_mini
{
	char *input;
	char **tokens;
	t_node node;
} t_mini;

char **create_token(t_mini mini);
void print_tokens(char **token);

#endif /* MINISHELL_H */