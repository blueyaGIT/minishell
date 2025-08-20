#include "minishell.h"

bool	is_tok_sep(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (true);
	return (false);
}

void	handle_empty_quote(t_token **token, int *i)
{
	token_add_back(token, new_token(T_WORD, ft_strdup("")));
	(*i) += 2;
}

void	handle_space(t_token **token, int *i)
{
	if (!token)
	{
		(*i)++;
		return ;
	}
	(*token)->add_space = true;
	(*i)++;
	return ;
}

int	check_assignment(char *input, int start)
{
	int	i;

	i = start;
	if (!ft_isalpha(input[i]) && input[i] != '_')
		return (0);
	while (input[i] && (ft_isalnum(input[i]) || input[i] == '_'))
		i++;
	return (input[i] == '=');
}
