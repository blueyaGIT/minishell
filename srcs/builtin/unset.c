/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalbano <dalbano@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 15:58:12 by dalbano           #+#    #+#             */
/*   Updated: 2025/04/12 17:14:28 by dalbano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_valid_identifier(t_shell *shell, char *str)
{
	int	idx;

	idx = env_idx(shell->env, str);
	if (idx == -1)
		return (0);
	return (idx);
}

static bool	remove_env_var(t_shell *shell, int idx)
{
	int	i;

	if (idx > ft_arrlen(shell->env))
		return (FAIL);
	ft_free_ptr(shell->env[idx]);
	i = idx;
	while (shell->env[i + 1])
	{
		shell->env[i] = ft_strdup(shell->env[i + 1]);
		ft_free_ptr(shell->env[i + 1]);
		i++;
	}
	shell->env = refresh_env(shell, i);
	if (!shell->env)
		return (FAIL);
	return (true);
}

int	exec_unset(t_shell *shell, char **args)
{
	int	i;
	int	exit_status;
	int	idx;

	exit_status = 0;
	i = 0;
	if (!args[0])
		return (print_error("unset: not enough arguments\n", shell), 1);
	while (args[i])
	{
		idx = is_valid_identifier(shell, args[i]);
		if (idx != -1)
		{
			if (remove_env_var(shell, idx) == false)
				return (print_error("unset: failed to remove var\n", shell), 1);
		}
		else
		{
			print_error("unset: '%s': not a valid identifier\n", shell);
			exit_status = 1;
		}
		i++;
	}
	return (exit_status);
}
