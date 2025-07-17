/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkloters <lkloters@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 13:18:53 by lkloters          #+#    #+#             */
/*   Updated: 2025/07/16 19:03:57 by lkloters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_token(t_token *token)
{
	if (!token)
		return ;
	token->value = NULL;
	token->type = 0;
	token->is_echo_n = false;
	token->next = NULL;
	token->prev = NULL;
}

bool	is_token_seperator(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (true);
	return (false);
}

int	calc_word_length(char *input, int i)
{
	int		length;
	char	quote;

	length = 0;
	while (input[i] && !is_token_seperator(input[i]) && !ft_isspace(input[i]))
	{
		if (input[i] == '\'' || input[i] == '\"')
		{
			quote = input[i++];
			while (input[i] && input[i] != quote)
			{
				length++;
				i++;
			}
			if (input[i] == quote)
				i++;
		}
		else
		{
			length++;
			i++;
		}
	}
	return (length);
}

void	handle_output_redirection(t_token **token, char *input, int *i)
{
	if (input[*i + 1] == '>')
	{
		token_add_back(token, new_token(T_APPEND, ft_strdup(">>")));
		(*i) += 2;
	}
	else
	{
		token_add_back(token, new_token(T_REDIR_OUT, ft_strdup(">")));
		(*i)++;
	}
}

void	handle_input_redirection(t_token **token, char *input, int *i)
{
	if (input[*i + 1] == '<')
	{
		token_add_back(token, new_token(T_HEREDOC, ft_strdup("<<")));
		(*i) += 2;
	}
	else
	{
		token_add_back(token, new_token(T_REDIR_IN, ft_strdup("<")));
		(*i)++;
	}
}
