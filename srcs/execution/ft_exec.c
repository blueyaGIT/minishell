/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalbano <dalbano@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 16:00:12 by dalbano           #+#    #+#             */
/*   Updated: 2025/04/24 17:10:07 by dalbano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	if_cmd_empty(t_shell *shell, t_command *cmd)
{
	int	i;

	if (!cmd || !cmd->command || cmd->command[0] == '\0')
	{
		if (cmd && cmd->args && cmd->args[1])
		{
			if (cmd->command)
				free(cmd->command);
			cmd->command = ft_strdup(cmd->args[1]);
			i = 1;
			while (cmd->args[i])
			{
				cmd->args[i - 1] = cmd->args[i];
				i++;
			}
			cmd->args[i - 1] = NULL;
			prep_cmd(shell, cmd);
			return ;
		}
		kill_shell(shell, EXIT_SUCCESS);
	}
}

int	prep_cmd(t_shell *shell, t_command *cmd)
{
	int	ecode;

	if (cmd && cmd->io && !check_io(cmd->io, true))
		kill_shell(shell, EXIT_FAILURE);
	if_cmd_empty(shell, cmd);
	fds_init(shell->cmd_list, cmd);
	if (!refresh_pipes(cmd->io))
		kill_shell(shell, EXIT_FAILURE);
	kill_fds(shell->cmd_list, false);
	if (ft_strchr(cmd->command, '/') == NULL)
	{
		ecode = exec_builtin(shell, cmd);
		if (ecode != 127)
			kill_shell(shell, ecode);
		ecode = exec_sys(shell, cmd);
		if (ecode != 127)
			kill_shell(shell, ecode);
	}
	ecode = exec_local(shell, cmd);
	kill_shell(shell, ecode);
	return (ecode);
}

int	exec_builtin(t_shell *shell, t_command *instr)
{
	int	temp;

	temp = 127;
	if (ft_strncmp(instr->command, "pwd", 4) == 0)
		temp = exec_pwd(shell);
	else if (ft_strncmp(instr->command, "env", 4) == 0)
		temp = exec_env(shell, instr->args);
	else if (ft_strncmp(instr->command, "exit", 5) == 0)
		temp = exec_exit(shell, instr->args);
	else if (ft_strncmp(instr->command, "cd", 3) == 0)
		temp = exec_cd(shell, instr->args);
	else if (ft_strncmp(instr->command, "echo", 5) == 0)
		temp = exec_echo(instr->args);
	else if (ft_strncmp(instr->command, "export", 7) == 0)
		temp = exec_export(shell, instr->args);
	else if (ft_strncmp(instr->command, "unset", 6) == 0)
		temp = exec_unset(shell, instr->args);
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
	if (!shell->cmd_list->pipe_flag && !shell->cmd_list->prev
		&& check_io(shell->cmd_list->io, false))
	{
		refresh_pipes(shell->cmd_list->io);
		temp = exec_builtin(shell, shell->cmd_list);
		refresh_io(shell->cmd_list->io);
	}
	if (temp != 127)
		return (temp);
	return (make_children(shell));
}
