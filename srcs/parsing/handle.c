/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkloters <lkloters@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 15:45:13 by lkloters          #+#    #+#             */
/*   Updated: 2025/07/02 11:04:05 by lkloters         ###   ########.fr       */
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
			i++;
		}
		else
			token_add_back(token, new_token(T_REDIR_OUT, ft_strdup(">")));
		i++;
	}
	if (input[*i] == '<')
	{
		if (input[*i + 1] == '<')
		{
			token_add_back(token, new_token(T_HEREDOC, ft_strdup("<<")));
			i++;
		}
		else
			token_add_back(token, new_token(T_REDIR_IN, ft_strdup("<")));
		i++;
	}
}

void handle_pipe(t_token **token, int *i)
{
	token_add_back(token, new_token(T_PIPE, ft_strdup("|")));
	(*i)++;
}

void handle_word(t_token **token, char *input, int *i)
{
	
}
