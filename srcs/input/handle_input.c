#include "minishell.h"

static char	*remove_quotes(const char *input)
{
	char		*result;
	size_t		i;
	size_t		j;
	char		quote;

	if (!input)
		return (NULL);
	result = (char *)malloc(sizeof(char) * (ft_strlen(input) + 1));
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (i < ft_strlen(input))
	{
		if (input[i] == '\'' || input[i] == '\"')
		{
			quote = input[i];
			if (input[i + 1] == quote)
				i += 2;
		}
		result[j++] = input[i++];
	}
	result[j] = '\0';
	return (result);
}

char	*handle_input(char *input, t_shell *shell)
{
	char	*result;
	char	*temp;

	if (!valid_input(input))
		return (NULL);
	temp = handle_env(shell);
	if (!temp)
		return (NULL);
	result = remove_quotes(temp);
	free(temp);
	return (result);
}
