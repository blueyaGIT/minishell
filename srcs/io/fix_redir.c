/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fix_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalbano <dalbano@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 14:46:26 by dalbano           #+#    #+#             */
/*   Updated: 2025/09/08 17:49:35 by dalbano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_infile(t_shell *shell)
{
	t_command	*cmd;

	cmd = shell->cmd_list;
	while (cmd)
	{
		if (cmd->io && cmd->io->infile)
		{
			cmd->io->fd_in = open(cmd->io->infile, O_RDONLY);
			if (cmd->io->fd_in == -1)
			{
				perror(cmd->io->infile);
				shell->last_exitcode = 1;
			}
		}
		cmd = cmd->next;
	}
}

void	handle_outfile(t_shell *shell)
{
	t_command	*cmd;

	cmd = shell->cmd_list;
	while (cmd)
	{
		if (cmd->io && cmd->io->outfile)
		{
			if (cmd->io->hrd_sep == T_APPEND)
				cmd->io->fd_out = open(cmd->io->outfile,
						O_CREAT | O_WRONLY | O_APPEND, 0644);
			else
				cmd->io->fd_out = open(cmd->io->outfile,
						O_CREAT | O_WRONLY | O_TRUNC, 0644);
			if (cmd->io->fd_out == -1)
			{
				perror(cmd->io->outfile);
				shell->last_exitcode = 1;
			}
		}
		cmd = cmd->next;
	}
}

void	fix_redir(t_shell *shell)
{
	if (!shell || !shell->cmd_list)
		return ;
	handle_outfile(shell);
	handle_infile(shell);
}
