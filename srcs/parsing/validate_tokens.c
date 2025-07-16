/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_tokens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkloters <lkloters@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 14:00:59 by lkloters          #+#    #+#             */
/*   Updated: 2025/07/16 13:24:48 by lkloters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	// if (token && token->prev && token->prev->type == T_PIPE)
	// 	return (false);
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
		return (false); // error message
	if (!valid_redirection_syntax(token))
		return (false); // error message
	if (!valid_command_syntax(token))
		return (false); // error message
	return (true);
}
