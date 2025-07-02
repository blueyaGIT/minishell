/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalbano <dalbano@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 13:43:01 by lkloters          #+#    #+#             */
/*   Updated: 2025/07/02 11:29:25 by dalbano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool ft_isspace_ms(char c)
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
		if (ft_isspace_ms(input[i]))
			i++;
		else if (input[i] == '|')
			handle_pipe();
		else if (is_redirectory(input[i]))
			handle_redirectory(&token, input, &i);
	}
}