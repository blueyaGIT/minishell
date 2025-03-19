/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_hrdc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalbano <dalbano@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:51:51 by dalbano           #+#    #+#             */
/*   Updated: 2025/03/19 13:31:00 by dalbano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Signalhandler for Ctrl+C in heredoc context
 * @param g_sig signals that SIGINT was received
 * @param rl_done Force readline to stop reading input
 * @param ioctl injects newline into terminal-input-buffer
 * @param TIOCSTI ensures proper exit of heredoc
 * @return terminates heredoc input on SIGINT
 */
void	ft_sigint_handler_heredoc(int signbr)
{
	(void)signbr;
	g_sig = 1;
	rl_done = 1;
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
	get_shell()->exit_code = 1;
}
