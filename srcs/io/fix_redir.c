/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fix_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalbano <dalbano@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 14:46:26 by dalbano           #+#    #+#             */
/*   Updated: 2025/09/24 17:56:57 by dalbano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_infile(t_shell *shell)
{
	t_command		*cmd;
	t_redir_file	*current_file;

	cmd = shell->cmd_list;
	while (cmd)
	{
		if (cmd->io && cmd->io->infiles)
		{
			current_file = cmd->io->infiles;
			while (current_file)
			{
				if (cmd->io->fd_in != -1)
					close(cmd->io->fd_in);
				cmd->io->fd_in = open(current_file->filename, O_RDONLY);
				if (cmd->io->fd_in == -1)
				{
					perror(current_file->filename);
					shell->last_exitcode = 1;
					break ;
				}
				current_file = current_file->next;
			}
		}
		cmd = cmd->next;
	}
}

void	handle_outfile(t_shell *shell)
{
	t_command		*cmd;
	t_redir_file	*current_file;

	cmd = shell->cmd_list;
	while (cmd)
	{
		if (cmd->io && cmd->io->outfiles)
		{
			current_file = cmd->io->outfiles;
			while (current_file)
			{
				if (cmd->io->fd_out != -1)
					close(cmd->io->fd_out);
				if (current_file->type == T_APPEND)
					cmd->io->fd_out = open(current_file->filename,
							O_CREAT | O_WRONLY | O_APPEND, 0644);
				else
					cmd->io->fd_out = open(current_file->filename,
							O_CREAT | O_WRONLY | O_TRUNC, 0644);
				if (cmd->io->fd_out == -1)
				{
					perror(current_file->filename);
					shell->last_exitcode = 1;
					break ;
				}
				current_file = current_file->next;
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
