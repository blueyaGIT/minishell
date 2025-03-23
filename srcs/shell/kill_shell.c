/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kill_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalbano <dalbano@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 16:21:36 by dalbano           #+#    #+#             */
/*   Updated: 2025/03/23 14:38:17 by dalbano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	kill_shell(t_shell *shell, int close_shell)
{
	dbmsg("Killing Shell");
	if (shell->heredoc_file)
		free(shell->heredoc_file);
	if (shell->cur_dir)
		free(shell->cur_dir);
	if (shell->history_file)
		free(shell->history_file);
	// gc_freeall();
	if (close_shell)
	{
		rl_clear_history();
		exit(shell->exit_code);
	}
	return (shell->exit_code);
}
