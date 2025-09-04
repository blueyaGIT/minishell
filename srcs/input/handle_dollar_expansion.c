#include "minishell.h"

static char	*copy_word(const char *str, int start)
{
	int		i;
	char	*word;
	int		word_length;

	if (!str || start < 0)
		return (NULL);
	i = start;
	while (str[i] && !ft_isspace((unsigned char)str[i]) && \
	str[i] != '$' && str[i] != '\'' && str[i] != '\"')
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

static char	*handle_env_val(char *dup, int start, int *end, t_shell *shell)
{
	char	*var_name;
	char	*env_value;
	char	*result;

	var_name = copy_word(dup, start);
	if (!var_name)
		return (dup);
	env_value = env_get(shell->env, var_name);
	*end = start + (int)ft_strlen(var_name);
	if (env_value)
	{
		result = ft_strdup(env_value);
		free(env_value);
	}
	else
		result = ft_strdup("");
	free(var_name);
	return (result);
}

static char	*handle_questionmark(int start, int *end)
{
	char	*result;

	result = ft_itoa(g_ecode);
	(*end) = start + 1;
	return (result);
}

char	*handle_dollar_exp(char *input_dup, int start, int *i, t_shell *shell)
{
	char	*new_input;
	int		end;
	char	*env_value;
	int		env_value_len;

	if (input_dup[start] == '?')
		env_value = handle_questionmark(start, &end);
	else
		env_value = handle_env_val(input_dup, start, &end, shell);
	if (!env_value)
	{
		(*i)++;
		return (input_dup);
	}
	env_value_len = (int)ft_strlen(env_value);
	new_input = replace_with_value(input_dup, start - 1, end, env_value);
	free(env_value);
	free(input_dup);
	if (!new_input)
		return (NULL);
	*i = (start - 1) + env_value_len;
	return (new_input);
}
