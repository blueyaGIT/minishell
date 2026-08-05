/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_signals.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkloters <lkloters@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/05 14:00:00 by lkloters          #+#    #+#             */
/*   Updated: 2026/08/05 14:00:00 by lkloters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_heredoc_signal(int signum)
{
	(void)signum;
	g_heredoc_interrupted = 1;
	write(STDOUT_FILENO, "\n", 1);
	siglongjmp(g_heredoc_jump, 1);
}

void	init_heredoc_signals(void)
{
	struct sigaction	sa;

	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = &handle_heredoc_signal;
	sigaction(SIGINT, &sa, NULL);
	g_heredoc_interrupted = 0;
}

void	restore_signals_after_heredoc(void)
{
	struct sigaction	sa;

	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = SIG_DFL;
	sigaction(SIGINT, &sa, NULL);
	g_heredoc_interrupted = 0;
}
