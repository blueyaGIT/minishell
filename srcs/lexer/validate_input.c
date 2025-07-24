#include "minishell.h"

static bool	valid_quotes(const char *input)
{
	int		i;
	char	quote;

	i = 0;
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '\"')
		{
			quote = input[i];
			i++;
			while (input[i] && input[i] != quote)
				i++;
			if (input[i] != quote)
				return (false);
			i++;
		}
		else
			i++;
	}
	return (true);
}

static bool	valid_escape_chars(const char *input)
{
	int		i;
	char	quote;

	i = 0;
	quote = 0;
	while (input[i])
	{
		if (quote == 0 && (input[i] == '\'' || input[i] == '\"'))
			quote = input[i];
		else if (quote == input[i])
			quote = 0;
		if (input[i] == '\\')
		{
			if (input[i + 1] == '\0')
				return (false);
			if (quote != '\'')
			{
				if (input[i + 1] == '\'')
					i++;
			}
			else
				i++;
		}
		i++;
	}
	return (true);
}

bool	valid_input(const char *input)
{
	if (!valid_quotes(input))
		return (ft_printf("minishell: syntax error: unclosed quote"), 1);
	if (!valid_escape_chars(input))
		return (ft_printf("minishell: syntax error: invalid backslash"), 1);
	return (true);
}
