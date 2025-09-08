/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refresh_pipes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalbano <dalbano@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 14:47:12 by dalbano           #+#    #+#             */
/*   Updated: 2025/09/08 14:47:13 by dalbano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	refresh_pipes(t_redir *io)
{
	bool	temp;

	temp = true;
	if (!io)
		return (temp);
	io->stdin_backup = dup(STDIN_FILENO);
	if (io->stdin_backup == -1)
		temp = false;
	io->stdout_backup = dup(STDOUT_FILENO);
	if (io->stdout_backup == -1)
		temp = false;
	if (io->fd_in != -1)
		if (dup2(io->fd_in, STDIN_FILENO) == -1)
			temp = false;
	if (io->fd_out != -1)
		if (dup2(io->fd_out, STDOUT_FILENO) == -1)
			temp = false;
	return (temp);
}
