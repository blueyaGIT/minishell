#include "../includes/minishell.h"

int main(void)
{
	t_mini mini = {0};
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

		if(syntax_error(mini.input) == 0)
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
		// enviroment_list(mini.list);
		ft_lstfree(mini.list);
		mini.list = NULL;
		free(mini.input);
	}

	return (0);
}