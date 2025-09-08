/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_io.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalbano <dalbano@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 14:46:28 by dalbano           #+#    #+#             */
/*   Updated: 2025/09/08 14:46:29 by dalbano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_redir(t_command *cmd)
{
	if (!cmd->io)
	{
		cmd->io = malloc(sizeof * cmd->io);
		if (!cmd->io)
			return ;
		cmd->io->infile = NULL;
		cmd->io->outfile = NULL;
		cmd->io->hrd_del = NULL;
		cmd->io->hrd_flag = false;
		cmd->io->fd_in = -1;
		cmd->io->fd_out = -1;
		cmd->io->stdin_backup = -1;
		cmd->io->stdout_backup = -1;
	}
}
