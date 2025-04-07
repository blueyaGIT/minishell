#include "minishell.h"

volatile sig_atomic_t	g_ecode = 0;

void leaks(void)
{
 printf("\n");
 system("leaks minishell");
}

static void	initialize_shell(t_shell *shell, char **argv, char **envp)
{
	(void)argv;
	ft_memset(shell, 0, sizeof(t_shell));
	if (shell_init(shell, envp) != success)
		exit(EXIT_FAILURE);
	// ft_print_logo(envp);
	// print_shell(shell);
}

int main(int argc, char *argv[], char **envp)
{
	// atexit(leaks);
	t_shell	shell;

	if (argc != 1)
		return (printf(RED "ERROR Input format: ./minishell\n" RESET));
	initialize_shell(&shell, argv, envp);
	while (1)
	{
		
		init_signals();
		shell.input = readline(PROMPT);
		if (!shell.input)
			break ;
		process_input(&shell);
		handle_syntax_and_exit(&shell);
		execute_commands(&shell);
		refresh_signals();
		if (ft_strcmp(shell.input, "./minishell") == 0)
			check_shlvl(&shell);
		g_ecode = ft_exec(&shell);
		refresh_shell(&shell);
	}
	kill_shell(&shell, 1);
	return (0);
}
