/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalbano <dalbano@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 16:00:12 by dalbano           #+#    #+#             */
/*   Updated: 2025/04/01 16:15:37 by dalbano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	prep_cmd(t_shell *shell, t_command *cmd)
{
	int	ecode;

	ecode = 127;
	if (!cmd || !cmd->command || !check_io(cmd->io, true))
		kill_shell(shell, EXIT_FAILURE);
	else if (cmd->command == NULL)
		kill_shell(shell, EXIT_FAILURE);
	fds_init(shell, cmd);
	if (!refresh_pipes(cmd->io))
		kill_shell(shell, EXIT_FAILURE);
	kill_fds(shell->cmd_list, false);
	if (ft_strchr(cmd->command, '/') == NULL)
	{
		ecode = exec_builtin(shell, cmd);
		if (ecode != 127)
			kill_shell(shell, ecode);
		ecode = exec_sys(shell, cmd, cmd->args);
		if (ecode != 127)
			kill_shell(shell, ecode);
	}
	ecode = exec_local(shell, cmd, cmd->args);
	kill_shell(shell, ecode);
	return (ecode);
}

int	exec_builtin(t_shell *shell, t_command *instr)
{
	int	temp;

	temp = 127;
	// if (!ft_strncmp(instr->command, "cd", 3))
	// 	temp = exec_cd(shell, instr->args);
	// else if (!ft_strncmp(instr->command, "echo", 5))
	// 	temp = exec_echo(shell, instr->args);
	// else if (!ft_strncmp(instr->command, "pwd", 4))
	// 	temp = exec_pwd(shell, instr->args);
	// else if (!ft_strncmp(instr->command, "export", 7))
	// 	temp = exec_export(shell, instr->args);
	// else if (!ft_strncmp(instr->command, "unset", 6))
	// 	temp = exec_unset(shell, instr->args);
	if (!ft_strncmp(instr->command, "env", 4))
		temp = exec_env(shell, instr->args);
	else if (!ft_strncmp(instr->command, "exit", 5))
		temp = exec_exit(shell, instr->args);
	shell->last_exitcode = temp;
	return (temp);
}

static int	check_data(t_shell *shell)
{
	if (!shell || !shell->cmd_list)
		return (EXIT_SUCCESS);
	if (!shell->cmd_list->command)
	{
		if (shell->cmd_list->io && !check_io(shell->cmd_list->io, true))
			return (EXIT_FAILURE);
		return (EXIT_SUCCESS);
	}
	if (!pipes_init(shell))
		return (EXIT_FAILURE);
	return (127);
}

int	ft_exec(t_shell *shell)
{
	int	temp;

	temp = check_data(shell);
	if (temp != 127)
		return (temp);
	if (!shell->cmd_list->pipe_flag && !shell->cmd_list->prev && !check_io(shell->cmd_list->io, false))
	{
		refresh_pipes(shell->cmd_list->io);
		temp = exec_builtin(shell, shell->cmd_list);
		refresh_io(shell->cmd_list->io);
	}
	if (temp != 127)
		return (temp);
	return (make_children(shell));
}
