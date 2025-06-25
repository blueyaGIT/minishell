/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalbano <dalbano@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 18:04:50 by dalbano           #+#    #+#             */
/*   Updated: 2025/04/10 14:40:52 by dalbano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_env(t_shell *shell, char **args)
{
	int	i;

	i = 0;
	if (args && args[1])
		return (printf(RED"ERROR: TOO MANY ARGUMENTS\n"RESET), 2);
	if (!shell->env)
		return (printf(RED"ERROR: ENV NOT FOUND\n"RESET), 1);
	while (shell->env[i])
		ft_putendl_fd(shell->env[i++], STDOUT_FILENO);
	return (EXIT_SUCCESS);
}
