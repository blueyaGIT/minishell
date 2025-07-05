/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkloters <lkloters@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 13:18:53 by lkloters          #+#    #+#             */
/*   Updated: 2025/07/05 14:15:08 by lkloters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool is_token_seperator(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (true);
	return (false);
}

int calc_word_length(char *input, int i)
{
	int length;
	char quote;
	length = 0;
	while (input[i] && !is_token_seperator(input[i]) && !ft_isspace(input[i]))
	{
		if(input[i] == '\'' || input[i] == '\"')
		{
			quote = input[i++];
			while(input[i] && input[i] != quote)
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
