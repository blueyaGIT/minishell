/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_word.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkloters <lkloters@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 16:32:31 by lkloters          #+#    #+#             */
/*   Updated: 2025/07/07 16:32:42 by lkloters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool is_filename(t_token *prev)
{
	if (!prev)
		return (false);
	if (prev->type == T_REDIR_IN || prev->type == T_REDIR_OUT || prev->type == T_APPEND)
		return (true);
}

static bool is_heredoc_delim(t_token *prev)
{
	if (!prev)
		return (false);
	if (prev->type == T_HEREDOC)
		return (true);
}

static bool is_assignment(const char *token)
{
    if (!token || !strchr(token, '='))
        return (false);
    if (token[0] == '=')
        return (false);
    const char *equals = strchr(token, '=');
    int name_len = equals - token;
    for (int i = 0; i < name_len; i++)
    {
        if (i == 0)
        {
            if (!isalpha(token[i]) && token[i] != '_')
                return false;
        }
        else
        {
            if (!isalnum(token[i]) && token[i] != '_')
                return false;
        }
    }
    return true;
}

// static bool is_command(t_token *token)
// {
// 	if (!token || token->type != T_WORD)
// 		return (false);
// 	t_token *prev = token->prev;
	
// }

void handle_word(t_token *token)
{
	t_token *prev;
	prev = NULL;
	while (token)
	{
		if (token->type == T_WORD)
		{
			if (is_filename(prev))
				token->word_type = FILENAME;
			else if (is_heredoc_delim(prev))
				token->word_type = HEREDOC_DELIM;
			else if (is_assignment(token->value))
				token->word_type = ASSIGNMENT;
			else if (is_builtin(token))
				token->word_type = BUILTIN;
			else if (is_command(token))
				token->word_type = COMMAND;
			else
				token->word_type = ARGUMENT;
		}
		prev = token;
		token = token->next;
	}
}