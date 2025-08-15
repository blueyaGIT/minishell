#include "minishell.h"

static bool	valid_quotes(const char *input)
{
	int		i;
	char	quote;

	if (!input)
		return (false);
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
		if (!quote && (input[i] == '\'' || input[i] == '\"'))
			quote = input[i];
		else if (quote && input[i] == quote)
			quote = 0;
		else if (input[i] == '\\')
		{
			if (!input[i + 1])
				return (false);
			if (quote != '\'')
				i++;
		}
		i++;
	}
	return (true);
}

bool	valid_input(const char *input)
{
	if (!valid_quotes(input))
		return (ft_printf("minishell: syntax error: unclosed quote\n"), 1); // muss readen wenn invalid input
	if (!valid_escape_chars(input))
		return (ft_printf("minishell: syntax error: invalid backslash\n"), 1); // nicht richtig gehandled
	return (true);
}
