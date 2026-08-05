/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_word.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalbano <dalbano@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 14:46:49 by dalbano           #+#    #+#             */
/*   Updated: 2025/09/08 14:49:04 by dalbano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_quoted_content(char *input, int *i, char *word, int *j)
{
	char	quote;
	char	next;

	quote = input[(*i)++];
	while (input[*i] && input[*i] != quote)
	{
		if (quote != '\'' && input[*i] == '\\' && input[*i + 1])
		{
			next = input[*i + 1];
			if (next == '$' || next == '"' || next == '\\' || next == '`')
			{
				(*i)++;
				word[(*j)++] = input[(*i)++];
			}
			else
				word[(*j)++] = input[(*i)++];
		}
		else
			word[(*j)++] = input[(*i)++];
	}
	if (input[*i] == quote)
		(*i)++;
	return (0);
}

static int	parse_word_content(char *input, int *i, char *word, int length)
{
	int	j;
	int	is_assign;

	j = 0;
	is_assign = check_assignment(input, *i);
	while (input[*i] && j < length)
	{
		if (input[*i] == '\'' || input[*i] == '\"')
			handle_quoted_content(input, i, word, &j);
		else if (input[*i] == '\\' && input[*i + 1])
			word[j++] = input[(*++i)++];
		else if (input[*i] == '=' && is_assign)
		{
			word[j++] = input[(*i)++];
			is_assign = 0;
		}
		else if ((ft_isspace(input[*i]) && !is_assign) || is_tok_sep(input[*i]))
			break ;
		else
			word[j++] = input[(*i)++];
	}
	word[j] = '\0';
	return (j);
}

static void	add_word_token(t_token **token, char *word)
{
	t_token			*new_tok;
	t_token_type	type;

	if (check_assignment(word, 0))
		type = ASSIGNMENT;
	else
		type = T_WORD;
	new_tok = new_token(type, word);
	if (!new_tok)
	{
		free(word);
		return ;
	}
	token_add_back(token, new_tok);
}

void	tokenize_word(t_token **token, char *input, int *i)
{
	char	*word;
	int		length;
	int		written;

	length = calc_word_length_with_assignment(input, *i);
	word = (char *)malloc(length + 1);
	if (!word)
		return ;
	written = parse_word_content(input, i, word, length);
	if (written < 0)
	{
		free(word);
		return ;
	}
	add_word_token(token, word);
}
