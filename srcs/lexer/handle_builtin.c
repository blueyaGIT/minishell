#include "minishell.h"

static bool	is_echo_option(const char *str)
{
	int	i;

	i = 1;
	if (str[0] != '-')
		return (false);
	while (str[i])
	{
		if (str[i] != 'n')
			return (false);
		i++;
	}
	return (true);
}

static bool	is_echo(t_token *token)
{
	t_token	*next;

	if (!token || ft_strcmp(token->value, "echo") != 0)
		return (false);
	next = token->next;
	while (next && next->type == T_WORD && is_echo_option(next->value))
		next = next->next;
	return (true);
}

bool	is_builtin(t_token *token)
{
	if (!token || token->type != T_WORD)
		return (false);
	if (is_echo(token))
		return (true);
	if (ft_strcmp(token->value, "cd") == 0 ||
	ft_strcmp(token->value, "pwd") == 0 ||
	ft_strcmp(token->value, "export") == 0 ||
	ft_strcmp(token->value, "unset") == 0 ||
	ft_strcmp(token->value, "env") == 0 ||
	ft_strcmp(token->value, "exit") == 0)
		return (true);
	return (false);
}
