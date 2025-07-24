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

static char	*replace_with_value(char *input, int start, int end, char *value)
{
	int		input_len;
	int		value_len;
	int		new_len;
	char	*new_input;

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
		result = ft_strdup(env_value);
	else
		result = ft_strdup("");
	return (result);
}

char	*handle_dollar_exp(char *input_dup, int start, int *i, t_shell *shell)
{
	char	*new_input;
	int		end;
	char	*env_value;

	env_value = handle_env_val(input_dup, start, &end, shell);
	if (!env_value)
	{
		(*i)++;
		return (input_dup);
	}
	new_input = replace_with_value(input_dup, start - 1, end, env_value);
	free(env_value);
	free(input_dup);
	if (!new_input)
		return (NULL);
	*i = (start - 1) + (int)ft_strlen(env_value);
	return (new_input);
}

char	*handle_tilde_exp(char *dup, int start, int *i, t_shell *shell)
{
	char	*new_input;
	char	*home_env;
	char	*home_path;
	int		end;

	end = start;
	while (dup[end] && dup[end] != '/' && !ft_isspace((unsigned char)dup[end]))
		end++;
	home_env = env_get(shell->env, "HOME");
	if (!home_env)
		home_path = ft_strdup("/");
	else
		home_path = ft_strdup(home_env);
	if (!home_path)
		return (dup);
	new_input = replace_with_value(dup, start - 1, end, home_path);
	if (!new_input)
	{
		free(home_path);
		return (NULL);
	}
	*i = (start - 1) + (int)ft_strlen(home_path);
	free(home_path);
	free(dup);
	return (new_input);
}
