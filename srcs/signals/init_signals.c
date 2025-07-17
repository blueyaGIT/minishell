

#include "minishell.h"

static void	print_nl(int temp)
{
	(void)temp;
	printf("\n");
	rl_on_new_line();
}

static void	refresh_rl(int signum)
{
	(void)signum;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	init_signals(void)
{
	struct sigaction	sa;

	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
	ft_memset(&sa, 0, sizeof(sa));
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
