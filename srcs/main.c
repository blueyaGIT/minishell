/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkloters <lkloters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 14:47:37 by dalbano           #+#    #+#             */
/*   Updated: 2025/09/24 11:11:55 by lkloters         ###   ########.fr       */
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
		init_signals(0);
		shell.input = read_line(PROMPT);
		if (!shell.input)
			break ;
		if (process_and_execute_input(&shell))
			g_ecode = ft_exec(&shell);
		else
			g_ecode = 1;
		reload_shell(&shell);
	}
	kill_shell(&shell, g_ecode);
	return (0);
}
