#include "minishell.h"

static bool	should_exp_tilde(const char *s, int i)
{
	if (i > 0 && !ft_isspace((unsigned char)s[i - 1]))
		return (false);
	if (!s[i + 1] || s[i + 1] == '/' || ft_isspace((unsigned char)s[i + 1]))
		return (true);
	return (false);
}

static bool	should_exp_env(char *input, int pos)
{
	int		i;
	bool	in_single_quotes;
	bool	in_double_quotes;

	if (!input || pos < 0 || input[pos] != '$')
		return (false);
	i = 0;
	in_single_quotes = false;
	in_double_quotes = false;
	while (i < pos)
	{
		if (input[i] == '\'' && !in_double_quotes)
			in_single_quotes = !in_single_quotes;
		else if (input[i] == '"' && !in_single_quotes)
			in_double_quotes = !in_double_quotes;
		i++;
	}
	if (in_single_quotes)
		return (false);
	if (pos + 1 >= (int)ft_strlen(input))
		return (false);
	if (!ft_isalnum(input[pos + 1]) && input[pos + 1] != '_')
		return (false);
	return (true);
}

static char	*make_expansion(char *input, int *i, t_shell *shell)
{
	char	expansion_char;
	int		start;
	char	*result;

	expansion_char = input[*i];
	(*i)++;
	start = *i;
	if (expansion_char == '$')
	{
		if (input[start] != '\0' && !ft_isspace((unsigned char)input[start]))
			result = handle_dollar_exp(input, start, i, shell);
		else
			result = input;
	}
	else if (expansion_char == '~')
		result = handle_tilde_exp(input, start, i, shell);
	else
		result = input;
	return (result);
}

static char	*env_to_input(char *input, t_shell *shell)
{
	int		i;
	char	*temp;

	if (!input || !shell)
		return (NULL);
	i = 0;
	while (input[i])
	{
		if ((input[i] == '$' && should_exp_env(input, i)) || (input[i] == '~' && should_exp_tilde(input, i)))
		{
			temp = make_expansion(input, &i, shell);
			if (!temp)
				return (NULL);
			input = temp;
		}
		else
			i++;
	}
	return (input);
}

char	*handle_env(t_shell *shell)
{
	char	*input_copy;
	char	*result;

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
