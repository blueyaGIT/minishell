/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_redirection.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalbano <dalbano@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 14:46:45 by dalbano           #+#    #+#             */
/*   Updated: 2025/09/08 14:46:46 by dalbano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_output_redirection(t_token **token, char *input, int *i)
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

static void	handle_input_redirection(t_token **token, char *input, int *i)
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

void	tokenize_redirection(t_token **token, char *input, int *i)
{
	if (input[*i] == '>')
		handle_output_redirection(token, input, i);
	else if (input[*i] == '<')
		handle_input_redirection(token, input, i);
}
