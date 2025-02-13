#include "../includes/minishell.h"
int main(void)
{
	t_mini mini;
	// t_token **tokens;

	// tokens = 0;
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

		if (ft_strcmp(mini.input, "exit") == 0)
		{
			printf("Good bye, see you ..👋 ");
			break;
		}
		mini.tokens = create_token(mini);
		printf("Prompt: %s\n", mini.input);
		convert_tokens(&mini);
		// printf(char)
		free(mini.input);
	}
	return (0);
}