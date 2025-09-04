#include "minishell.h"

static bool	valid_pipe_syntax(t_token *token)
{
	if (!token)
		return (false);
	if (token->type == T_PIPE)
		return (false);
	while (token)
	{
		if (token->type == T_PIPE)
		{
			if (!token->next || token->next->type == T_PIPE)
				return (false);
			if (!token->prev || token->prev->type == T_PIPE)
				return (false);
		}
		token = token->next;
	}
	return (true);
}

static bool	valid_redirection_syntax(t_token *token)
{
	if (!token)
		return (false);
	if (is_redirection_token(token))
		return (false);
	while (token)
	{
		if (is_redirection_token(token))
		{
			if (!token->next)
				return (false);
			if (is_redirection_token(token->next) || \
			token->next->type == T_PIPE)
				return (false);
			token = token->next;
		}
		token = token->next;
	}
	return (true);
}

bool	valid_syntax(t_token *token)
{
	if (!token)
		return (false);
	if (!valid_pipe_syntax(token))
	{
		ft_printf("minishell: syntax error: invalid pipe\n");
		return (false);
	}
	if (!valid_redirection_syntax(token))
	{
		ft_printf("minishell: syntax error near unexpected token 'newline'\n");
		return (false);
	}
	return (true);
}
