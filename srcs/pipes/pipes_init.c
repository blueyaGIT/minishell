/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkloters <lkloters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 14:47:11 by dalbano           #+#    #+#             */
/*   Updated: 2025/09/08 14:54:45 by lkloters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	close_created_pipes(t_command *cmd_list)
{
	t_command	*temp;

	temp = cmd_list;
	while (temp)
	{
		if (temp->pipe_fd)
		{
			close(temp->pipe_fd[0]);
			close(temp->pipe_fd[1]);
			free(temp->pipe_fd);
			temp->pipe_fd = NULL;
		}
		temp = temp->next;
	}
}

static bool	create_pipe_for_cmd(t_shell *shell, t_command *cmd)
{
	int	*fd;

	fd = malloc(sizeof * fd * 2);
	if (!fd)
	{
		close_created_pipes(shell->cmd_list);
		reload_shell(shell);
		return (false);
	}
	if (pipe(fd) != 0)
	{
		free(fd);
		close_created_pipes(shell->cmd_list);
		reload_shell(shell);
		return (false);
	}
	cmd->pipe_fd = fd;
	return (true);
}

bool	pipes_init(t_shell *shell)
{
	t_command	*temp;

	temp = shell->cmd_list;
	while (temp)
	{
		if (temp->pipe_flag || (temp->prev && temp->prev->pipe_flag))
		{
			if (!create_pipe_for_cmd(shell, temp))
				return (false);
		}
		temp = temp->next;
	}
	return (true);
}

bool	fds_init(t_command *temp, t_command *cmd)
{
	if (!cmd)
		return (false);
	if (cmd->prev && cmd->prev->pipe_flag)
	{
		if (dup2(cmd->prev->pipe_fd[0], STDIN_FILENO) == -1)
			return (false);
	}
	if (cmd->pipe_flag)
	{
		if (dup2(cmd->pipe_fd[1], STDOUT_FILENO) == -1)
			return (false);
	}
	kill_pipes(temp, cmd);
	return (true);
}
