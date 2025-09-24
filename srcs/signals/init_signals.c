/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_signals.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkloters <lkloters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 10:25:51 by lkloters          #+#    #+#             */
/*   Updated: 2025/09/24 16:28:59 by lkloters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


static void    parent_handler(int sig)
{
    if (sig == SIGINT)
    {
        g_ecode = 130;
        write(STDOUT_FILENO, "^C\n", 3);
        rl_replace_line("", 0);
        rl_on_new_line();
        rl_redisplay();
    }
    else if (sig == SIGQUIT)
        g_ecode = 0;
    else if (sig == SIGTSTP)
        g_ecode = 0;
}
static void child_handler(int sig)
{
    if (sig == SIGINT)
    {
        g_ecode = 130;
        write(STDOUT_FILENO, "\n", 1);
        exit(130);
    }
    else if (sig == SIGQUIT)
    {
        g_ecode = 131;
        write(STDOUT_FILENO, "Quit: 3\n", 9);
        exit(131);
    }
}

void	init_signals(int is_child)
{
	struct sigaction	sa;

	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);

	if (is_child == 0)
	{
		sa.sa_handler = &parent_handler;
		sigaction(SIGINT, &sa, NULL);
		sigaction(SIGQUIT, &sa, NULL);
		sigaction(SIGTSTP, &sa, NULL);
		rl_catch_signals = 0;
	}
	else if (is_child == 1)
	{
		sa.sa_handler = &child_handler;
		sigaction(SIGINT, &sa, NULL);
		sigaction(SIGQUIT, &sa, NULL);
	}
	else if (is_child == 2)
	{
		sa.sa_handler = SIG_IGN;
		sigaction(SIGINT, &sa, NULL);
		sigaction(SIGQUIT, &sa, NULL);
	}
}