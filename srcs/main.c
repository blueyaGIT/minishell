/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalbano <dalbano@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 14:47:37 by dalbano           #+#    #+#             */
/*   Updated: 2025/09/08 15:40:29 by dalbano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	initialize_shell(t_shell *shell, char **argv, char **envp)
{
	(void)argv;
	ft_memset(shell, 0, sizeof(t_shell));
	if (!shell_init(shell, envp))
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
		shell.input = read_line(PROMPT);
		refresh_signals();
		if (!shell.input)
			break ;
		if (ft_strcmp(shell.input, "./minishell") == 0)
			check_shlvl(&shell);
		if (process_and_execute_input(&shell))
			g_ecode = ft_exec(&shell);
		else
			g_ecode = 1;
		// print_shell(&shell);
		reload_shell(&shell);
	}
	kill_shell(&shell, g_ecode);
	return (0);
}
