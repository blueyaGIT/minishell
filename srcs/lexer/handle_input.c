/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkloters <lkloters@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 15:45:13 by lkloters          #+#    #+#             */
/*   Updated: 2025/07/05 14:21:03 by lkloters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void handle_redirectory(t_token **token, char *input, int *i)
{
    if (input[*i] == '>')
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
    else if (input[*i] == '<')
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
}

void handle_pipe(t_token **token, int *i)
{
	token_add_back(token, new_token(T_PIPE, ft_strdup("|")));
	(*i)++;
}

void handle_empty_quote(t_token **token, int *i)
{
	token_add_back(token, new_token(T_WORD, ft_strdup("")));
	(*i) += 2;
}

static int parse_word_content(char *input, int *i, char *word, int length)
{
	int j;
	char quote;
	
	j = 0;
	while (input[*i] && j < length)
	{
		if (input[*i] == '\'' || input[*i] == '\"')
		{
			quote = input[(*i)++];
			while (input[*i] && input[*i] != quote && j < length)
				word[j++] = input[(*i)++];
			if (input[*i] == quote)
				(*i)++;
		}
		else
			word[j++] = input[(*i)++];
	}
	word[j] = '\0';
	return (j);
}


void handle_word(t_token **token, char *input, int *i)
{
	char *word;
	int length;
	int written;

	length = calc_word_length(input, *i);
	word = (char *)malloc(length + 1);
	if (!word)
		return ;
	written = parse_word_content(input, i, word, length);
	if (written < 0)
	{
		free(word);
		return ;
	}
	token_add_back(token, new_token(T_WORD, word));
	free(word);
}
