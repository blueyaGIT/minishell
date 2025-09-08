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

	quote = input[(*i)++];
	while (input[*i] && input[*i] != quote)
		word[(*j)++] = input[(*i)++];
	if (input[*i] == quote)
		(*i)++;
	return (0);
}

static int	handle_assignment_char(char *input, int *i, char *word, int *j)
{
	word[(*j)++] = input[(*i)++];
	return (0);
}

static int	parse_word_content(char *input, int *i, char *word, int length)
{
	int		j;
	int		is_assign;

	j = 0;
	is_assign = check_assignment(input, *i);
	while (input[*i] && j < length)
	{
		if (input[*i] == '\'' || input[*i] == '\"')
			handle_quoted_content(input, i, word, &j);
		else if (input[*i] == '=' && is_assign)
		{
			handle_assignment_char(input, i, word, &j);
			is_assign = 0;
		}
		else if (ft_isspace(input[*i]) && !is_assign)
			break ;
		else
			word[j++] = input[(*i)++];
	}
	word[j] = '\0';
	return (j);
}

void	tokenize_word(t_token **token, char *input, int *i)
{
	char			*word;
	int				length;
	int				written;
	t_token_type	type;

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
	if (check_assignment(word, 0))
		type = ASSIGNMENT;
	else
		type = T_WORD;
	token_add_back(token, new_token(type, word));
}
