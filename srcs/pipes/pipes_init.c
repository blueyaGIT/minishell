/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalbano <dalbano@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 17:20:13 by dalbano           #+#    #+#             */
/*   Updated: 2025/04/24 17:04:36 by dalbano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	pipes_init(t_shell *shell)
{
	int			fd[2];
	t_command	*temp;

	temp = shell->cmd_list;
	while (temp)
	{
		if (temp->pipe_flag || (temp->prev && temp->prev->pipe_flag))
		{
			if (pipe(fd) != 0)
			{
				reload_shell(shell);
				return (false);
			}
			temp->pipe_fd = fd;
		}
		temp = temp->next;
	}
	return (SUCCESS);
}

bool	fds_init(t_command *temp, t_command *cmd)
{
	if (!cmd)
		return (false);
	if (cmd->prev && cmd->prev->pipe_flag)
		dup2(cmd->prev->pipe_fd[0], STDIN_FILENO);
	if (cmd->pipe_flag)
		dup2(cmd->pipe_fd[1], STDOUT_FILENO);
	kill_pipes(temp, cmd);
	return (true);
}
