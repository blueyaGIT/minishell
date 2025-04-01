/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalbano <dalbano@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 17:20:13 by dalbano           #+#    #+#             */
/*   Updated: 2025/04/01 13:42:01 by dalbano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	pipes_init(t_shell *shell)
{
	int			*fd;
	t_command	*instr;

	instr = shell->cmd_list;
	while (instr)
	{
		if (instr->pipe_flag || (instr->prev && instr->prev->pipe_flag))
		{
			fd = malloc(sizeof(*fd) * 2);
			if (!fd || pipe(fd) != 0)
				return (refresh_shell(shell), fail);
			instr->pipe_fd = fd;
		}
		instr = instr->next;
	}
	return (success);
}

bool	fds_init(t_shell *shell, t_command *cmd)
{
	if (!cmd)
		return (false);
	if (cmd->prev && cmd->prev->pipe_fd)
		dup2(cmd->prev->pipe_fd[0], STDIN_FILENO);
	if (cmd->pipe_fd)
		dup2(cmd->pipe_fd[1], STDOUT_FILENO);
	kill_pipes(shell->cmd_list, cmd);
	return (true);
}
