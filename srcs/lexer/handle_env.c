#include "minishell.h"

static char *make_expansion(char *input, int *i, t_shell *shell)
{
	char expansion_char;
	int start;
	char *result;

	expansion_char = input[*i];
	(*i)++;
	start = *i;
	if (expansion_char == '$')
		result = handle_dollar_expansion(input, start, i, shell);
	else if (expansion_char == '~')
		result = handle_tilde_expansion(input, start, i, shell);
	else
		result = input;
	return (result);
}

static char *env_to_input(char *input, t_shell *shell)
{
	int i;
	char *temp;

	if (!input || !shell)
		return (NULL);
	i = 0;
	while (input[i])
	{
		if(input[i] == '$' || input[i] == '~')
		{
			temp = make_expansion(input, &i, shell);
			if (!temp)
				return (NULL);
			free(input);
			input = temp;
		}
		else
			i++;
	}
	return (input);
}

char *handle_env(t_shell *shell)
{
	char *input_copy;
	char *result;

	if (!shell || !shell->input)
		return (NULL);
	input_copy = ft_strdup(shell->input);
	if (!input_copy)
		return (NULL);
	result = env_to_input(input_copy, shell);
	if (!result)
	{
		free(input_copy);
		return (NULL);
	}
	return (result);
}
