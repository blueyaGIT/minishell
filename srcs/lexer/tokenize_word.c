/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_word.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkloters <lkloters@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 16:32:31 by lkloters          #+#    #+#             */
/*   Updated: 2025/07/15 15:17:59 by lkloters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_filename(t_token *prev)
{
	if (!prev)
		return (false);
	if (prev->type == T_REDIR_IN || prev->type == T_REDIR_OUT || \
		prev->type == T_APPEND)
		return (true);
	return (false);
}

static bool	is_heredoc_delim(t_token *prev)
{
	if (!prev)
		return (false);
	if (prev->type == T_HEREDOC)
		return (true);
	return (false);
}

static bool	is_assignment(const char *token)
{
	int			i;
	const char	*equals;
	int			name_len;

	i = 0;
	if (!token || !strchr(token, '='))
		return (false);
	if (token[0] == '=')
		return (false);
	equals = strchr(token, '=');
	name_len = equals - token;
	while (i < name_len)
	{
		if ((i == 0 && !isalpha(token[i]) && token[i] != '_') || \
		(i > 0 && !isalnum(token[i]) && token[i] != '_'))
			return (false);
		i++;
	}
	return (true);
}

static bool	is_command(t_token *token)
{
	t_token	*current;

	if (!token || token->type != T_WORD)
		return (false);
	if (!token->prev)
		return (true);
	if (token->prev->type == T_PIPE)
		return (true);
	current = token->prev;
	while (current && current->type != T_PIPE)
	{
		if (current->type == COMMAND || current->type == BUILTIN)
			return (false);
		current = current->prev;
	}
	return (true);
}

void	tokenize_word_token(t_token *token)
{
	while (token)
	{
		if (token->type == T_WORD)
		{
			if (is_filename(token->prev))
				token->type = FILENAME;
			else if (is_heredoc_delim(token->prev))
				token->type = HEREDOC_DELIM;
			else if (is_assignment(token->value))
				token->type = ASSIGNMENT;
			else if (is_builtin(token))
				token->type = BUILTIN;
			else if (is_command(token))
				token->type = COMMAND;
			else
				token->type = ARGUMENT;
		}
		token = token->next;
	}
}
