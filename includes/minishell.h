#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include "libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>

typedef enum e_token_type
{
	WORD,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	HEREDOC,
	APPEND,
	DOUBLEQUOTED,
	SINGLEQUOTED,
}t_token_type;

typedef struct s_node
{
	char *args;
	char **filename;
	char **redirections;
} t_node;

typedef struct s_token
{
	char *token_value;
	t_token_type type;
}	t_token;


typedef struct s_mini
{
	char *input;
	char **tokens;
	t_node node;
} t_mini;

char **create_token(t_mini mini);
void print_tokens(t_token **tokens);
t_token	**convert_tokens(char **tokens);
t_token_type	token_type(char *token);
const char *token_type_to_string(t_token_type type);

#endif /* MINISHELL_H */