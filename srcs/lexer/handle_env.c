#include "minishell.h"

static char *copy_word(const char *str, int start)
{
	int i;
	char *word;
	int word_length;

	if (!str || start < 0)
		return (NULL);
	i = start;
	while (str[i] && !ft_isspace((unsigned char)str[i]) && str[i] != '$')
		i++;
	word_length = i - start;
	if (word_length == 0)
		return (NULL);
	word = malloc(sizeof (char) * (word_length + 1));
	if (!word)
		return (NULL);
	ft_memcpy(word, &str[start], word_length);
	word[word_length] = '\0';
	return (word);
}

static char *replace_with_value(char *input, int start, int end, char *value)
{
	int input_len;
	int value_len;
	int new_len;
	char *new_input;

	if (!input || !value || start < 0 || end < start)
		return (NULL);
	input_len = (int)ft_strlen(input);
	value_len = (int)ft_strlen(value);
	new_len = input_len - (end - start) + value_len;
	new_input = (char *)malloc(sizeof (char) * (new_len + 1));
	if (!new_input)
		return (NULL);
	ft_memcpy(new_input, input, start);
	ft_memcpy(new_input + start, value, value_len);
	ft_memcpy(new_input + start + value_len, input + end, input_len - end);
	new_input[new_len] = '\0';
	return (new_input);
}


static char *handle_env(char *input_dup, int start, int *i, t_shell *shell)
{
	char *found_dollar;
	char *env_value;
	char *new_input;
	int end;

	found_dollar = copy_word(input_dup, start);
	if (!found_dollar)
	{
		(*i)++;
		return (input_dup);
	}
	env_value = env_get(shell->env, found_dollar);
	end = start + (int)ft_strlen(found_dollar);
	if (env_value)
	{
		new_input = replace_with_value(input_dup, start - 1, end, env_value);
		free(env_value);
		free(found_dollar);
		free(input_dup);
		if (!new_input)
			return (NULL);
		*i = (start - 1) + (int)ft_strlen(env_value);
		return (new_input);
	}
	else
	{
		free(found_dollar);
		(*i) = end;
		return (input_dup);
	}
}


char *check_env(char *input, t_shell *shell)
{
	int i;
	char *new_input;
	int start;

	if (!input || !shell)
		return (NULL);
	new_input = ft_strdup(input);
	if (!new_input)
		return (NULL);
	i = 0;
	while (new_input[i])
	{
		if (new_input[i] == '$')
		{
			i++;
			start = i;
			new_input = handle_env(new_input, start, &i, shell);
			if (!new_input)
				return (NULL);
		}
		else
			i++;
	}
	return (new_input);
}

			