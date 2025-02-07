#include "../../includes/minishell.h"

char **create_token(t_mini mini)
{
	int i = 0;
	char **tokens;
	char *start = mini.input;
	char *end;
	tokens = malloc(sizeof(char *) * 100);
	if (!tokens)
		return NULL;
	while (*start)
	{
		while (*start == ' ')
			start++;
		if (*start == '|' || *start == '<' || *start == '>')
		{
			tokens[i++] = strndup(start, 1);
			start++;
		}
		else
		{
			end = start;
			while (*end && *end != '<' && *end != '>' && *end != '|' && *end != ' ')
				end++;
			tokens[i++] = strndup(start, end - start);
			start = end;
		}
	}
	tokens[i] = NULL;
	return tokens;
}

