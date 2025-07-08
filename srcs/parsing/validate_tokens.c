/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_tokens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkloters <lkloters@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 14:00:59 by lkloters          #+#    #+#             */
/*   Updated: 2025/07/08 15:40:36 by lkloters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool valid_redirection_syntax(t_token *token)
{
	if (!token)
		return (false);
	while (token && token->next)
	{
		if(token->type == T_REDIR_IN || token->type == T_REDIR_OUT || token->type == T_APPEND || token->type == T_HEREDOC)
		{
			if (!token->next || token->next->type == T_WORD)
				return (false);
			if (token->word_type == T_HEREDOC && token->next->word_type == HEREDOC_DELIM)
				return (false);
			else if (token->type != T_HEREDOC && token->next->word_type != FILENAME)
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
		if (token->type == T_WORD)
		{
			if ((token->word_type != COMMAND && token->word_type != BUILTIN) && !has_command)
				return (false);
			if (token->word_type == COMMAND || token->word_type == BUILTIN)
			{
				if (has_command)
					return (false);
				has_command = true;
			}
		}
		if (token->type == T_PIPE)
			has_command = false;
		token = token->next;
	}
	return (true);
}

bool valid_tokens(t_token *token)
{
	if (!token)
		return (false);
	if (!valid_redirection_synatx(token))
		return (false); // error message
	if (!valid_command_syntax(token))
		return (false); // error message
	return (true);
}
