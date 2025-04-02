/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalbano <dalbano@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 14:50:06 by dalbano           #+#    #+#             */
/*   Updated: 2025/04/02 17:47:53 by dalbano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_dir(char *cmd)
{
	struct stat	cmd_stat;

	ft_memset(&cmd_stat, 0, sizeof(cmd_stat));
	stat(cmd, &cmd_stat);
	return (S_ISDIR(cmd_stat.st_mode));
}

int	exec_sys(t_shell *shell, t_command *cmd)
{
	if (!cmd->command || cmd->command[0] == '\0' || is_dir(cmd->command))
		return (127);
	cmd->cpath = find_command_path(shell, cmd->command);
	if (cmd->cpath == NULL)
		return (127);
	cmd->args = ft_str_to_array_front(cmd->args, cmd->command);
	if (execve(cmd->cpath, cmd->args, shell->env) == -1)
		return (errno);
	return (EXIT_FAILURE);
}

int	exec_local(t_shell *shell, t_command *cmd, char **args)
{
	if (ft_strchr(cmd->command, '/') == NULL && env_idx(shell->env,
		"PATH") != -1)
		return (127);
	if (access(cmd->command, F_OK) != 0)
		return (printf(RED"ERROR: No such file or directory"RESET), 127);
	if (is_dir(cmd->command))
		return (printf(RED"ERROR: Command is a Directory"RESET), 126);
	if (access(cmd->command, F_OK | X_OK) != 0)
		return (printf(RED"ERROR: Permission denied"RESET), 126);
	if (execve(cmd->command, args, shell->env) == -1)
		return (errno);
	return (EXIT_FAILURE);
}
