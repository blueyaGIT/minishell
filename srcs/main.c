#include "minishell.h"

volatile sig_atomic_t g_sig = 0;

// static bool	empty_input(char *temp)
// {
// 	int	i;

// 	i = 0;
// 	while (temp[i])
// 	{
// 		if (!ft_isspace(temp[i]))
// 			return (fail);
// 		i++;
// 	}
// 	return (success);
// }

// static bool	check_input(t_shell *shell)
// {
// 	if (!shell->input)
// 		kill_builtin(shell, NULL);
// 	else if (!*shell->input)
// 		return (success);
// 	add_history(shell->input);
// 	if (empty_input(shell->input))
// 		return (success);
// 	if (make_token(shell, shell->input) == 1)
// 		return (fail);
// 	if (shell->token_ll->type == END)
// 		return (fail);
// }

static void initialize_shell(t_shell *shell, char **argv, char **envp)
{
	(void) argv;
    ft_memset(shell, 0, sizeof(t_shell));
    if (shell_init(shell, envp) != success)
        exit(EXIT_FAILURE);
    ft_print_logo(envp);
    print_shell(shell);
}

int main(int argc, char *argv[], char **envp)
{
	t_shell	shell;

	if (argc != 1)
		return (printf(RED"ERROR Input format: ./minishell\n"RESET));
	initialize_shell(&shell, argv, envp);
	while (1)
	{
		init_signals();
		shell.input = readline(PROMPT);
		if (!shell.input)
			break;
		process_input(&shell);
		handle_syntax_and_exit(&shell);
		execute_commands(&shell);
		refresh_signals();
		// if (ft_strcmp(shell.input, "./minishell") == 0)
		// 	check_shlvl(&shell);
		// if (check_input(&shell))
		// 	g_sig = ft_exec(&shell);
		// else
		// 	g_sig = 1;
		refresh_shell(&shell);
	}
	kill_shell(&shell, 1);
	return (0);
}
