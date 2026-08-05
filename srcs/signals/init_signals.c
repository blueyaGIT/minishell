/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_signals.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalbano <dalbano@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 10:25:51 by lkloters          #+#    #+#             */
/*   Updated: 2025/09/24 18:12:45 by dalbano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		g_heredoc_interrupted = 0;
jmp_buf	g_heredoc_jump;

static void	print_nl(int temp)
{
	(void)temp;
	write(STDOUT_FILENO, "\n", 1);
}

static void	refresh_rl(int signum)
{
	(void)signum;
	write(STDOUT_FILENO, "\n", 1);
}

static void	sig_ignore(void)
{
	struct sigaction	sa;

	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
	sigaction(SIGTSTP, &sa, NULL);
}

void	init_signals(void)
{
	struct sigaction	sa;

	sig_ignore();
	ft_memset(&sa, 0, sizeof(sa));
	if (getenv("MINISHELL_CHILD"))
		sa.sa_handler = &print_nl;
	else
		sa.sa_handler = &refresh_rl;
	sigaction(SIGINT, &sa, NULL);
}

void	refresh_signals(void)
{
	struct sigaction	sa;

	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = &print_nl;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}
