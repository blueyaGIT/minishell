/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refresh_pipes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalbano <dalbano@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 17:44:18 by dalbano           #+#    #+#             */
/*   Updated: 2025/03/25 17:44:24 by dalbano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	refresh_pipes(t_redir *io)
{
	if (!io)
		return (true);
	io->stdin_backup = dup(STDIN_FILENO);
	if (io->stdin_backup == -1)
		return (printf(RED"ERROR: FAILED SETTING STDIN_BACKUP IN REFRESH_PIPES"RESET), fail);
	io->stdout_backup = dup(STDOUT_FILENO);
	if (io->stdout_backup == -1)
		return (printf(RED"ERROR: FAILED SETTING STDOUT_BACKUP IN REFRESH_PIPES"RESET), fail);
	if (io->fd_in != -1)
		if (dup2(io->fd_in, STDIN_FILENO) == -1)
			return (printf(RED"ERROR: FAILED DUP2 STDIN_FILENO IN REFRESH_PIPES"RESET), fail);
	if (io->fd_out != -1)
		if (dup2(io->fd_out, STDOUT_FILENO) == -1)
			return (printf(RED"ERROR: FAILED DUP2 STDOUT_FILENO IN REFRESH_PIPES"RESET), fail);
	return (success);
}
