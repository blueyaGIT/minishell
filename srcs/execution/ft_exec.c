/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalbano <dalbano@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 16:00:12 by dalbano           #+#    #+#             */
/*   Updated: 2025/03/25 18:34:22 by dalbano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_builtin(t_shell *shell, t_command *instr)
{
	int	temp;

	temp = 2;
	if (ft_strncmp(instr->command, "cd", 3))
		temp = exec_cd(shell, instr->args);
	else if (ft_strncmp(instr->command, "echo", 5))
		temp = exec_echo(shell, instr->args);
	else if (ft_strncmp(instr->command, "pwd", 4))
		temp = exec_pwd(shell, instr->args);
	else if (ft_strncmp(instr->command, "export", 7))
		temp = exec_export(shell, instr->args);
	else if (ft_strncmp(instr->command, "unset", 6))
		temp = exec_unset(shell, instr->args);
	else if (ft_strncmp(instr->command, "env", 4))
		temp = exec_env(shell, instr->args);
	else if (ft_strncmp(instr->command, "exit", 5))
		temp = exec_exit(shell, instr->args);
	return (temp);
}

static int	check_data(t_shell *shell)
{
	if (!shell || !shell->command_ll)
		return (EXIT_SUCCESS);
	if (!shell->command_ll->command)
	{
		if (shell->command_ll->io && !check_io(shell->command_ll->io, true))
			return (EXIT_FAILURE);
		return (EXIT_SUCCESS);
	}
	if (!pipes_init(shell))
		return (EXIT_FAILURE);
	return (2);
}

int	ft_exec(t_shell *shell)
{
	int	temp;

	temp = check_data(shell);
	if (temp != 2)
		return (temp);
	if (!shell->command_ll->pipe_flag && !shell->command_ll->prev && !check_io(shell->command_ll->io, false))
	{
		refresh_pipes(shell->command_ll->io);
		temp = exec_builtin(shell, shell->command_ll);
		refresh_io(shell->command_ll->io);
	}
	if (temp != 2)
		return (temp);
	return (make_children(shell));
}
