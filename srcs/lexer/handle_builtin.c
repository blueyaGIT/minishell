/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalbano <dalbano@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 17:02:36 by lkloters          #+#    #+#             */
/*   Updated: 2025/07/09 16:21:47 by dalbano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool is_echo_option(const char *str)
{
	int i;
	
	i = 1;
	if (str[0] != '-')
		return (false);
	while (str[i])
	{
		if (str[i] != 'n')
			return (false);
	}
	return (true);
}

static bool is_echo(t_token *token)
{
	if (!token || ft_strcmp(token->value, "echo") != 0)
		return (false);
	t_token *next = token->next;
	while (next && next->type == T_WORD && is_echo_option(next->value))
	next = next->next;
	return (true);
}

bool is_builtin(t_token *token)
{
	if (!token || token->type != T_WORD)
		return (false);
	if (is_echo(token))
		return (true);
	if (ft_strcmp(token->value, "cd") == 0 || \
	ft_strcmp(token->value, "pwd") == 0 || \
	ft_strcmp(token->value, "export") == 0 || \
	ft_strcmp(token->value, "unset") == 0 || \
	ft_strcmp(token->value, "env") == 0 || \
	ft_strcmp(token->value, "exit") == 0)
        return true;
    return false;
}