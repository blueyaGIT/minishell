/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkloters <lkloters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 14:46:37 by dalbano           #+#    #+#             */
/*   Updated: 2025/09/22 16:45:50 by lkloters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_echo_option(const char *str)
{
	int	i;

	i = 1;
	if (str[0] != '-')
		return (false);
	if (str[1] == '\0')
		return (false);
	while (str[i])
	{
		if (str[i] != 'n')
			return (false);
		i++;
	}
	return (true);
}

static bool	is_echo(t_token *token)
{
	t_token	*current;

	if (!token || ft_strcmp(token->value, "echo") != 0)
		return (false);
	current = token->next;
	token->is_echo = true;
	while (current && current->type == T_WORD && is_echo_option(current->value))
	{
		token->is_echo_n = true;
		current->is_removed = true;
		current = current->next;
	}
	return (true);
}

static bool	is_shell_builtin_name(char *name)
{
	if (ft_strcmp(name, "cd") == 0)
		return (true);
	if (ft_strcmp(name, "pwd") == 0)
		return (true);
	if (ft_strcmp(name, "export") == 0)
		return (true);
	if (ft_strcmp(name, "unset") == 0)
		return (true);
	if (ft_strcmp(name, "env") == 0)
		return (true);
	if (ft_strcmp(name, "exit") == 0)
		return (true);
	return (false);
}

bool	is_builtin(t_token *token)
{
	if (!token || token->type != T_WORD)
		return (false);
	if (is_echo(token))
		return (true);
	return (is_shell_builtin_name(token->value));
}
