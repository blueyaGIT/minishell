#include "../includes/minishell.h"

int main(int argc, char *argv[], char **env)
{
	(void) argv;
	(void) argc;
	t_mini mini = {0};
	mini.env = copy_env(env);
	while (1)
	{
		mini.input = readline("🧚:");
		if (!mini.input)
		{
			printf(" End of File. End of Minishell! \n");
			break;
		}
		if (*mini.input)
			add_history(mini.input);

		char *expanded_input = expand_variables(mini.input, mini.env, mini.last_exitcode);
		// char *expanded_input = expand_variables(mini.input, mini.env);
		free(mini.input);  
		mini.input = expanded_input;
		
		int syntax_result = syntax_error(mini.input);
		if(syntax_result == 0 && check_unclosed_quotes(mini.input) == 0)
		{
			if (ft_strcmp(mini.input, "exit") == 0)
			{
				printf("Good bye, see you ..👋 ");
				break;
			}
			mini.tokens = create_token(mini);
			printf("Prompt: %s\n", mini.input);
			convert_tokens(&mini);
			print_token_list(mini.list);
		}

		if(syntax_result != 0 )
		{
			mini.last_exitcode = 2;
		}
		else 
			mini.last_exitcode = 0;
		build_parsing_nodes(&mini);
		print_node_list(mini.node);
		ft_lstfree(mini.list);
		mini.list = NULL;
		free(mini.input);
	}
	free_env(mini.env);
	return (0);
}
