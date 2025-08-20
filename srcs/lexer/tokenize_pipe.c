#include "minishell.h"

void	tokenize_pipe(t_token **token, int *i)
{
	token_add_back(token, new_token(T_PIPE, ft_strdup("|")));
	(*i)++;
}
