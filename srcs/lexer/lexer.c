/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkloters <lkloters@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 13:43:01 by lkloters          #+#    #+#             */
/*   Updated: 2025/07/09 13:09:04 by lkloters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool is_redirection(char c)
{
	if (c == '<' || c == '>')
		return (true);
	return (false);
}

static bool before_is_word(char *input, int i)
{
	unsigned char c;
	if (i <= 0)
		return (false);
		c = (unsigned char)input[i - 1];
	if (ft_isalnum(c) || c == '_')
		return (true);
	return (false);
}
static bool after_is_word(char *input, int i)
{
	unsigned char c;
	if (input[i + 1] == '\0')
		return (false);
	c = (unsigned char)input[i + 1];
	if (ft_isalnum(c) || c == '_')
		return (true);
	return (false);
}

static bool is_empty_quote(char *input, int i)
{
	char c;
	c = input[i];
	if ((c == '\'' || c == '\"') && input[i + 1] == c)
	{
		if (before_is_word(input, i) || after_is_word(input, i))
			return (false);
		else
			return (true);
	}
	return (false);
}

t_token *lexer(char *input)
{
	t_token *token = NULL;
	int i = 0;

	if (!valid_input(input))
		return (NULL);
	while (input[i])
	{
		if (ft_isspace(input[i]))
			i++;
		else if (input[i] == '|')
			handle_pipe(&token, &i);
		else if (is_redirection(input[i]))
			handle_redirection(&token, input, &i);
		else if (is_empty_quote(input, i))
			handle_empty_quote(&token, &i);
		else
			handle_word(&token, input, &i);
	}
	tokenize_word(token);
	return (token);
}
