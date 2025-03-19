/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_signals.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalbano <dalbano@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:47:24 by dalbano           #+#    #+#             */
/*   Updated: 2025/03/19 13:31:08 by dalbano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_signal_handler(int signbr, void (*handler)(int))
{
	struct sigaction	sa;

	sa.sa_handler = handler;
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	if (sigaction(signbr, &sa, NULL) == -1)
	{
		perror("sigaction");
		exit(EXIT_FAILURE);
	}
}

void	switch_to_normal_mode(void)
{
	set_signal_handler(SIGINT, ft_sigint_handler_normal);
	set_signal_handler(SIGQUIT, SIG_IGN);
}

void	switch_to_heredoc_mode(void)
{
	set_signal_handler(SIGINT, ft_sigint_handler_heredoc);
	set_signal_handler(SIGQUIT, SIG_IGN);
}

void	init_signals(void)
{
	rl_catch_signals = 0;
	switch_to_normal_mode();
}
