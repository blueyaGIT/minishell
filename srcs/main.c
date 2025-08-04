
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
		if (isatty(fileno(stdin)))
			shell.input = read_line(PROMPT);
		else
		{
			char *line;
			line = get_next_line(fileno(stdin));
			shell.input = ft_strtrim(line, "\n");
			free(line);
		}
		refresh_signals();
		if (!shell.input)
			break ;
		if (ft_strcmp(shell.input, "./minishell") == 0)
			check_shlvl(&shell);
		if (process_and_execute_input(&shell))
			g_ecode = ft_exec(&shell);
		else
			g_ecode = 1;
		reload_shell(&shell);
	}
	kill_shell(&shell, g_ecode);
	return (0);
}
