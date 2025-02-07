#include "../includes/minishell.h"
int main(void)
{
	t_mini mini;
	char **tokens;
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

		if (strcmp(mini.input, "exit") == 0)
		{
			printf("Good bye, see you ..👋 ");
			break;
		}

		// mini.input = malloc(sizeof(char) * (strlen(mini.input) + 1));
		create_token(mini);

		printf("Prompt: %s\n", mini.input);
		tokens = create_token(mini);
		print_tokens(tokens);
		free(mini.input);
	}
	return (0);
}