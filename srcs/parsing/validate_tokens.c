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

// static bool	valid_command_syntax(t_token *token)
// {
// 	bool	has_command;

// 	has_command = false;
// 	if (!token)
// 		return (false);
// 	while (token)
// 	{
// 		if (token->type == COMMAND || token->type == BUILTIN)
// 		{
// 			if (has_command)
// 				return (false);
// 			has_command = true;
// 		}
// 		else if (is_redirection_token(token))
// 		{
// 			if (!token)
// 		}
// 		if (token->type == T_PIPE)
// 		{
// 			if (!has_command)
// 				return (false);
// 			has_command = false;
// 		}
// 		token = token->next;
// 	}
// 	if (!has_command)
// 		return (false);
// 	return (true);
// }

bool	valid_syntax(t_token *token)
{
	if (!token)
		return (false);
	if (!valid_pipe_syntax(token))
	{
		ft_printf("minishell: syntax error: invalid pipe\n");
		return (false); // needs to read again until valid input
	}
	if (!valid_redirection_syntax(token))
	{
		ft_printf("minishell: syntax error near unexpected token 'newline'\n");
		return (false);
	}
	// if (!valid_command_syntax(token))
	// {
	// 	ft_printf("minishell: syntax error: invalid command\n");
	// 	return (false);
	// }
	return (true);
}
