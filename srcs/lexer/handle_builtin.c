#include "minishell.h"

static bool	is_echo_option(const char *str)
{
	int	i;

	i = 1;
	if (str[0] != '-')
		return (false);
	if (str[1] == '\0')
		return (false);
	while (str[i])
	{
		if (str[i] != 'n')
			return (false);
		i++;
	}
	return (true);
}

static void	ft_remove_token(t_token **head, t_token *prev, t_token *echo_option)
{
	if (!echo_option)
		return ;
	if (prev)
		prev->next = echo_option->next;
	else
		*head = echo_option->next;
	free(echo_option->value);
	free(echo_option);
}

static bool	is_echo(t_token *token)
{
	t_token	*current;
	t_token	*prev;

	if (!token || ft_strcmp(token->value, "echo") != 0)
		return (false);
	current = token->next;
	prev = token;
	while (current && current->type == T_WORD && is_echo_option(current->value))
	{
		token->is_echo_n = true;
		ft_remove_token(&token->next, prev, current);
		current = prev->next;
	}
	return (true);
}

bool	is_builtin(t_token *token)
{
	if (!token || token->type != T_WORD)
		return (false);
	if (is_echo(token))
		return (true);
	if (ft_strcmp(token->value, "cd") == 0 || \
	ft_strcmp(token->value, "pwd") == 0 || \
	ft_strcmp(token->value, "export") == 0 || \
	ft_strcmp(token->value, "unset") == 0 || \
	ft_strcmp(token->value, "env") == 0 || \
	ft_strcmp(token->value, "exit") == 0)
		return (true);
	return (false);
}
