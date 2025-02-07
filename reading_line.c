#include "minishell.h"
char *one_space(t_mini mini)
{
	int i = 0;
	int j = 0;
	char *trim;
	int space_found = 1;
	char quote = 0;

	trim = malloc(sizeof(char) * (strlen(mini.input) + 1));
	if (!trim)
		return NULL;

	while (mini.input[i])
	{
		if(quote)
		{
			trim[j++] = mini.input[i];
			if(mini.input[i] == quote)
				quote = 0;
		}
		else
		{
		if(mini.input[i] == '\'' || mini.input[i]== '"')
		{
			quote = mini.input[i];
			trim[j++] = mini.input[i];
		}
		else if (mini.input[i] != ' ')
		{
			trim[j++] = mini.input[i];
			space_found = 0;
		}
		else if (!space_found)
		{
			trim[j++] = ' ';
			space_found = 1;
		}
		}
		i++;
	}
	if (j > 0 && trim[j - 1] == ' ')
		j--;
	trim[j] = '\0';
	return (trim);
}

char *create_token(t_mini mini)
{
	int i = 0;
	char **tokens;
	char *start = mini.input;
	while(*start)
	{
		while(*start = ' ')
		{
			start ++;
		}
		if(*start == '|' || *start == '<' || *start == '>')
		{
			tokens[i] = strndup(start, 1);
				i++;
				
		}
	}
}


int main()
{
	t_mini mini;
	char *input;
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
		mini.input = one_space(mini);
		// prom = put_space_after_tube(prom);
		if(strcmp(mini.input, "exit") == 0)
		{
			printf("Good bye, see you ..👋 ");
			break;
		}
		printf(" Prompt: %s \n", mini.input);

		free(mini.input);
	}
	return (0);
}