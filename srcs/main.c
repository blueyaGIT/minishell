#include "minishell.h"

volatile sig_atomic_t g_sig = 0;

int main(int argc, char *argv[], char **envp)
{
	t_shell	*shell;

	ft_print_logo();
	init_signals();
	(void) argv;
	(void) argc;
	shell = get_shell();
	shell->shell_dir = getcwd(NULL, 0);
	shell->heredoc_file = gc_strjoin(shell->shell_dir, HEREDOC_FILE);
	shell->heredoc_index = -1;	
	shell->history_file = gc_strjoin(shell->shell_dir, HISTORY_FILE);
	if (isatty(STDIN_FILENO))
		history_init();
	if (argc != 1 || shell_init(shell, envp))
		return (1);
	// t_mini mini = {0};
	// mini.env = copy_env(env);
	// while (1)
	// {
	// 	mini.input = readline("🧚:");
	// 	if (!mini.input)
	// 	{
	// 		printf(" End of File. End of Minishell! \n");
	// 		break ;
	// 	}
	// 	if (*mini.input)
	// 		add_history(mini.input);

	// 	if(syntax_error(mini.input) == 0)
	// 	{
	// 		if (ft_strcmp(mini.input, "exit") == 0)
	// 		{
	// 			printf("Good bye, see you ..👋 ");
	// 			break;
	// 		}
	// 		mini.tokens = create_token(mini);
	// 		printf("Prompt: %s\n", mini.input);
	// 		convert_tokens(&mini);
	// 		print_token_list(mini.list);
	// 	}
	// 	build_parsing_nodes(&mini);
	// 	print_node_list(mini.node);
	// 	ft_lstfree(mini.list);
	// 	mini.list = NULL;
	// 	free(mini.input);
	// }
	// free_env(mini.env);
	return (0);
}
