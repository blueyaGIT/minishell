/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kill_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalbano <dalbano@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 16:21:36 by dalbano           #+#    #+#             */
/*   Updated: 2025/03/25 15:34:19 by dalbano          ###   ########.fr       */
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
	if (close_shell)
	{
		rl_clear_history();
		exit(shell->last_exitcode);
	}
	return (shell->last_exitcode);
}
