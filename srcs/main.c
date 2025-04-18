/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalbano <dalbano@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 14:34:35 by dalbano           #+#    #+#             */
/*   Updated: 2025/04/11 16:19:59 by dalbano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_ecode = 0;

// void leaks(void)
// {
//  printf("\n");
//  system("leaks minishell");
// }
// atexit(leaks);

static void	initialize_shell(t_shell *shell, char **argv, char **envp)
{
	(void)argv;
	ft_memset(shell, 0, sizeof(t_shell));
	if (shell_init(shell, envp) != SUCCESS)
		exit(EXIT_FAILURE);
	ft_print_logo(envp);
}

int	main(int argc, char *argv[], char **envp)
{
	t_shell	shell;

	if (argc != 1)
		return (ft_printf(RED "ERROR Input format: ./minishell\n" RESET));
	initialize_shell(&shell, argv, envp);
	while (1)
	{
		init_signals();
		shell.input = readline(PROMPT);
		if (!shell.input || shell.input[0] == '\0')
		{
			set_exit_code(&shell, 0);
			continue ;
		}
		process_and_execute_input(&shell);
		refresh_signals();
		if (ft_strcmp(shell.input, "./minishell") == 0)
			check_shlvl(&shell);
		g_ecode = ft_exec(&shell);
		reload_shell(&shell);
	}
	kill_shell(&shell, 1);
	return (0);
}
