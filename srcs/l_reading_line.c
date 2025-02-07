#include "../includes/minishell.h"
void print_tokens(char **token)
{
	int i = 0;
	while (token[i])
	{
		printf("Token[%d]: %s\n", i, token[i]);
		i++;
	}
}

char **create_token(t_mini mini)
{
	int i = 0;
	char *start = mini.input;
	char *end;
	mini.tokens = malloc(sizeof(char *) * 100);
	if (!mini.tokens)
		return NULL;
	while (*start)
	{
		while (*start == ' ')
			start++;
		if ((*start == '<' && start[1] == '<') || (*start == '>' && start[1] == '>'))
		{
			mini.tokens[i++] = strndup(start, 2);
			start += 2;
		}
		else if (*start == '|' || *start == '<' || *start == '>')
		{
			mini.tokens[i++] = strndup(start, 1);
			start++;
		}
		else
		{
			end = start;
			while (*end && *end != '<' && *end != '>' && *end != '|' && *end != ' ')
				end++;
			mini.tokens[i++] = strndup(start, end - start);
			start = end;
		}
	}
	mini.tokens[i] = NULL;
	return mini.tokens;
}
