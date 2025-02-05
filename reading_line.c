#include "minishell.h"
char *one_space(char *prom)
{
	int i = 0;
	int j = 0;
	char *trim;
	int space_found = 1;
	char quote = 0;

	trim = malloc(sizeof(char) * (strlen(prom) + 1));
	if (!trim)
		return NULL;

	while (prom[i])
	{
		if(quote)
		{
			trim[j++] = prom[i];
			if(prom[i] == quote)
				quote = 0;
		}
		else
		{
		if(prom[i] == '\'' || prom[i]== '"')
		{
			quote = prom[i];
			trim[j++] = prom[i];
		}
		else if (prom[i] != ' ')
		{
			trim[j++] = prom[i];
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
	return trim;
}


int main()
{
	char *prom;
	while (1)
	{
		prom = readline("🧚:");
		if (!prom)
		{
			printf(" End of File. End of Minishell! \n");
			break;
		}
		if (*prom)
			add_history(prom);
		prom = one_space(prom);
		// prom = put_space_after_tube(prom);
		printf(" Prompt: %s \n", prom);
		free(prom);
	}
	return (0);
}