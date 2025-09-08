/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fix_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalbano <dalbano@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 14:46:26 by dalbano           #+#    #+#             */
/*   Updated: 2025/09/08 14:46:27 by dalbano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_infile(t_shell *shell)
{
	if (!shell->cmd_list->io->infile)
		return ;
	shell->cmd_list->io->fd_in = open(shell->cmd_list->io->infile, O_RDONLY);
	if (shell->cmd_list->io->fd_in == -1)
	{
		perror(shell->cmd_list->io->infile);
		shell->last_exitcode = 1;
	}
}

void	handle_outfile(t_shell *shell)
{
	if (!shell->cmd_list->io->outfile)
		return ;
	if (shell->cmd_list->io->hrd_sep == T_APPEND)
		shell->cmd_list->io->fd_out = open(shell->cmd_list->io->outfile,
				O_CREAT | O_WRONLY | O_APPEND, 0644);
	else
		shell->cmd_list->io->fd_out = open(shell->cmd_list->io->outfile,
				O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (shell->cmd_list->io->fd_out == -1)
	{
		perror(shell->cmd_list->io->outfile);
		shell->last_exitcode = 1;
	}
}

void	fix_redir(t_shell *shell)
{
	if (!shell || !shell->cmd_list || !shell->cmd_list->io)
		return ;
	handle_outfile(shell);
	handle_infile(shell);
}
