#include "minishell.h"

static bool valid_pipe_syntax(t_token *token)
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


static bool valid_redirection_syntax(t_token *token)
{
	if (!token)
		return (false);
	while (token)
	{
		if(token->type == T_REDIR_IN || token->type == T_REDIR_OUT || token->type == T_APPEND || token->type == T_HEREDOC)
		{
			if (!token->next)
				return (false);
			if (token->type == T_HEREDOC && token->next->type != HEREDOC_DELIM)
				return (false);
			else if (token->next->type != FILENAME)
					return (false);
			token = token->next;
		}
		token = token->next;
	}
	return (true);
}

static bool valid_command_syntax(t_token *token)
{
	bool has_command = false;
	if (!token)
		return (false);
	while (token)
	{
		if (token->type == COMMAND || token->type == BUILTIN)
		{
			if (has_command)
				return (false);
			has_command = true;
		}
		if (token->type == T_PIPE)
		{
			if (!has_command)
				return (false);
			has_command = false;
		}
		token = token->next;
	}
	if (!has_command)
		return (false);
	return (true);
}

bool valid_syntax(t_token *token)
{
	if (!token)
		return (false);
	if (!valid_pipe_syntax(token))
		return (ft_printf("minishell: syntax error: invalid pipe", 0));
	if (!valid_redirection_syntax(token))
		return (ft_printf("minishell: syntax error: invalid redirection", 0));
	if (!valid_command_syntax(token))
		return (ft_printf("minishell: syntax error: invalid command", 0));
	return (true);
}
