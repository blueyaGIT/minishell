/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkloters <lkloters@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 13:43:01 by lkloters          #+#    #+#             */
/*   Updated: 2025/07/01 17:40:56 by lkloters         ###   ########.fr       */
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

t_token *lexer(char *input)
{
	t_token *token = NULL;
	int i = 0;

	while (input[i])
	{
		if (ft_isspace(input[i]))
			i++;
		else if (input[i] == '|')
			handle_pipe();
		else if (is_redirectory(input[i]))
			handle_redirectory(&token, input, &i);
	}
}