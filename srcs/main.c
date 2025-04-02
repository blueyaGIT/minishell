// #include "minishell.h"

// volatile sig_atomic_t g_sig = 0;

// int main(int argc, char *argv[], char **envp)
// {
// 	t_shell	shell;
// 	t_mini mini = {0};

// 	if (argc != 1)
// 		return (printf(RED"ERROR Input format: ./minishell\n"RESET));
// 	ft_memset(&shell, 0, sizeof(t_shell));
// 	if (shell_init(&shell, envp) != success)
// 		exit(EXIT_FAILURE);
// 	ft_print_logo(envp);
// 	print_shell(&shell);

// 	(void) argv;

// 	while (1)
// 	{
// 		mini.input = readline("🧚:");
// 		if (!mini.input)
// 		{
// 			printf(" End of File. End of Minishell! \n");
// 			break;
// 		}
// 		if (*mini.input)
// 			add_history(mini.input);

// 		char *expanded_input = expand_variables(mini.input, mini.env, shell.last_exitcode);
// 		// char *expanded_input = expand_variables(mini.input, mini.env);
// 		free(mini.input);  
// 		mini.input = expanded_input;
		
// 		int syntax_result = syntax_error(mini.input);
// 		if(syntax_result == 0 && check_unclosed_quotes(mini.input) == 0)
// 		{
// 			if (ft_strcmp(mini.input, "exit") == 0)
// 			{
// 				printf("Good bye, see you ..👋 ");
// 				break;
// 			}
// 			mini.tokens = create_token(mini);
// 			printf("Prompt: %s\n", mini.input);
// 			convert_tokens(&mini);
// 			print_token_list(mini.list);
// 		}

// 		if(syntax_result != 0 )
// 		{
// 			shell.last_exitcode = 2;
// 		}
// 		else 
// 			shell.last_exitcode = 0;
// 		build_parsing_nodes(&mini);
// 		print_node_list(mini.node);
// 		ft_lstfree(mini.list);
// 		mini.list = NULL;
// 		free(mini.input);
// 	}
// 	ft_free_arr(mini.env);
// 	return (0);
// }


#include "minishell.h"

volatile sig_atomic_t g_sig = 0;

void initialize_shell(t_shell *shell, char **envp)
{
    ft_memset(shell, 0, sizeof(t_shell));
    if (shell_init(shell, envp) != success)
        exit(EXIT_FAILURE);
    ft_print_logo(envp);
    print_shell(shell);
}

void process_input( t_shell *shell)
{
    shell->input = readline("\xf0\x9f\xa7\x9a:");
    if (!shell->input)
    {
        printf(" End of File. End of Minishell! \n");
        exit(0);
    }
    if (*(shell->input))
        add_history(shell->input);

    char *expanded_input = expand_variables(shell->input, shell->env, shell->last_exitcode);
    free(shell->input);
    shell->input = expanded_input;
}

int handle_syntax_and_exit(t_shell *shell)
{
    run_syntax_checks(shell);
    if (ft_strcmp(shell->input, "exit") == 0)
{
    printf("Good bye, see you ..\n");
    return 1;
}
char *expanded = expand_variables(shell->input, shell->env, shell->last_exitcode);
free(shell->input);
shell->input = expanded;

shell->tokens = create_token(*shell);
printf("Prompt: %s\n", shell->input);
convert_tokens(shell);
print_token_list(shell->list);

return 0;
}
void execute_commands(t_shell *shell)
{
	build_parsing_nodes(shell); 

	print_node_list(shell->node); 
	shell->cmd_list = convert_node_list_to_command_list(shell->node);
	print_command_list(shell->cmd_list);
	ft_lstfree(shell->list);
	shell->list = NULL;
	free(shell->input);
}
int main(int argc, char *argv[], char **envp)
{
    t_shell shell;
    if (argc != 1)
        return (printf(RED"ERROR Input format: ./minishell\n"RESET));
    initialize_shell(&shell, envp);
    (void) argv;
    while (1)
    {
        process_input( &shell);
        if (handle_syntax_and_exit(&shell))
            break;
        execute_commands( &shell);
    }
    ft_free_arr(shell.env);
    return (0);
}