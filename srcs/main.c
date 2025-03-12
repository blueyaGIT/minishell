#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	t_shell	*minishell;

	(void)ac;
	(void)av;
	(void)env;
	init_signals();
	write_log("Program started.");
	// tokens = 0;
	t_mini mini = {0};	
	ft_print_logo();
	while (1)
	{
		mini.input = readline("🧚:");
		if (!mini.input)
		{
			printf(" End of File. End of Minishell! \n");
			break ;
		}
		if (*mini.input)
			add_history(mini.input);

		if (ft_strcmp(mini.input, "exit") == 0)
		{
			printf("Goodbye, cya next time ..👋 ");
			break ;
		}
		mini.tokens = create_token(mini);
		printf("Prompt: %s\n", mini.input);
		convert_tokens(&mini);
		print_token_list(mini.list);
		// enviroment_list(mini.list);
		ft_lstfree(mini.list);
		mini.list = NULL;
		free(mini.input);
	}
	write_log("Program closed by 'exit'.");
	return (0);
}
