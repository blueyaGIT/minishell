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
		printf("hello\n");
		if (ft_strcmp(shell.input, "./minishell") == 0)
			check_shlvl(&shell);
		printf("hello1\n");
		if (process_and_execute_input(&shell))
		{
			printf("hello2\n");
			g_ecode = ft_exec(&shell);
			printf("hello3\n");
		}
		else
			g_ecode = 1;
		printf("hello4\n");
		reload_shell(&shell);
		printf("hello5\n");
	}
	kill_shell(&shell, g_ecode);
	return (0);
}
