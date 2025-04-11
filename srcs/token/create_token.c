/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalbano <dalbano@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 15:20:57 by dalbano           #+#    #+#             */
/*   Updated: 2025/04/11 15:24:20 by dalbano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// /*debug zum drucekn von der Liste */
// void	print_token_list(t_list *list)
// {
// 	t_token	*token_data;

// 	while (list)
// 	{
// 		token_data = (t_token *)list->content;
// 		if (token_data)
// 			printf("tk: %-15s | tp: %d\n", token_data->token_value,
// 					token_data->tp);
// 		list = list->next;
// 	}
// }
/**/
int	count_words(const char *str)
{
	int	count;
	int	in_word;

	count = 0;
	in_word = 0;
	while (*str)
	{
		if (*str != ' ' && in_word == 0)
		{
			in_word = 1;
			count++;
		}
		else if (*str == ' ')
			in_word = 0;
		str++;
	}
	return (count);
}

char	*create_quote_token(char **start)
{
	char	quote;
	char	*end;
	char	*tk;

	quote = **start;
	(*start)++;
	end = *start;
	while (*end && *end != quote)
		end++;
	if (*end == quote)
		end++;
	tk = ft_strndup((*start) - 1, end - (*start) + 1);
	*start = end;
	return (tk);
}

char	*create_word_token(char **start)
{
	char	*end;
	char	*tk;

	end = *start;
	while (*end && *end != '<' && *end != '>' && *end != '|' && *end != ' ')
		end++;
	tk = ft_strndup(*start, end - *start);
	*start = end;
	return (tk);
}

static char	*get_next_token(char **start)
{
	char	*tk;

	while (**start == ' ')
		(*start)++;
	if (!**start)
		return (NULL);
	if (**start == '"' || **start == '\'')
		return (create_quote_token(start));
	else if ((**start == '<' && (*start)[1] == '<') || (**start == '>'
			&& (*start)[1] == '>'))
	{
		tk = ft_strndup(*start, 2);
		*start += 2;
		return (tk);
	}
	else if (**start == '|' || **start == '<' || **start == '>')
	{
		tk = ft_strndup(*start, 1);
		(*start)++;
		return (tk);
	}
	else
		return (create_word_token(start));
}

char	**create_token(t_shell shell)
{
	int		num;
	char	*start;
	char	*tk;

	num = 0;
	start = shell.input;
	shell.tokens = ft_calloc(sizeof(char *), ft_strlen(start) + 1);
	if (!shell.tokens)
		return (NULL);
	tk = get_next_token(&start);
	while (tk != NULL)
	{
		shell.tokens[num++] = tk;
		tk = get_next_token(&start);
	}
	shell.tokens[num] = NULL;
	return (shell.tokens);
}
