/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkloters <lkloters@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 13:43:01 by lkloters          #+#    #+#             */
/*   Updated: 2025/07/02 14:10:16 by lkloters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool ft_isspace(char c)
{
	if (c == ' ' || c == '\t')
		return (true);
	return (false);
}

bool is_redirectory(char c)
{
	if (c == '<' || c == '>' || c == '<<' || c == '>>')
		return (true);
	return (false);
}

bool is_empty_quote(char *input, int *i)
{
	char c;
	c = input[*i];
	if ((c == '\'' || c == '\"') && input[*i + 1] == c)
	{
		if (before_is_word(input, *i) && after_is_word(input, *i))
			return (false);
		return (true);
	}
	return (false);
}

t_token *lexer(char *input)
{
	t_token *token = NULL;
	int i = 0;

	while (input[i])
	{
		if (ft_isspace(input[i]))
			i++;
		else if (input[i] == '|')
			handle_pipe(&token, &i);
		else if (is_redirectory(input[i]))
			handle_redirectory(&token, input, &i);
		else if (is_empty_quote)
			handle_empty_quote();
		else
			handle_word()
	}
}