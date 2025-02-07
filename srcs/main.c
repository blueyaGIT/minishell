#include "../includes/minishell.h"
int main(void)
{
	t_mini mini;
	char *input;
	char *token;

	input = NULL;
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
		token = *create_token(mini);
		printf("token: %s", token);
		printf("Prompt: %s\n", mini.input);
		free(mini.input);
	}
	return (0);
}