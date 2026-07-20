/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalbano <dalbano@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 14:46:16 by dalbano           #+#    #+#             */
/*   Updated: 2025/09/08 14:46:17 by dalbano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	should_exp_tilde(const char *s, int i)
{
	if (i > 0 && !ft_isspace((unsigned char)s[i - 1]))
		return (false);
	if (!s[i + 1] || s[i + 1] == '/' || ft_isspace((unsigned char)s[i + 1]))
		return (true);
	return (false);
}

static bool	should_exp_env(char *input, int pos, bool ignore_quotes)
{
	int		i;
	bool	in_single_quotes;
	bool	in_double_quotes;
	bool	escaped;

	if (!input || pos < 0 || input[pos] != '$')
		return (false);
	i = 0;
	in_single_quotes = false;
	in_double_quotes = false;
	escaped = false;
	while (i < pos)
	{
		if (escaped)
			escaped = false;
		else if (!ignore_quotes && input[i] == '\'' && !in_double_quotes)
			in_single_quotes = !in_single_quotes;
		else if (!ignore_quotes && input[i] == '"' && !in_single_quotes)
			in_double_quotes = !in_double_quotes;
		else if (input[i] == '\\' && !in_single_quotes)
			escaped = true;
		i++;
	}
	if (escaped || in_single_quotes)
		return (false);
	if (pos + 1 >= (int)ft_strlen(input))
		return (false);
	if (!ft_isalnum(input[pos + 1]) && input[pos + 1] != '_' && input[pos
			+ 1] != '?')
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

static char	*env_to_input(char *input, t_shell *shell, bool ignore_quotes)
{
	int		i;
	char	*temp;

	if (!input || !shell)
		return (NULL);
	i = 0;
	while (input[i])
	{
		if ((input[i] == '$' && should_exp_env(input, i, ignore_quotes))
			|| (input[i] == '~' && should_exp_tilde(input, i)))
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

static char	*expand_env_impl(char *str, t_shell *shell, bool ignore_quotes)
{
	char	*input_copy;
	char	*result;

	if (!str || !shell)
		return (NULL);
	input_copy = ft_strdup(str);
	if (!input_copy)
		return (NULL);
	result = env_to_input(input_copy, shell, ignore_quotes);
	if (!result)
	{
		free(input_copy);
		return (NULL);
	}
	return (result);
}

char	*expand_env_string(char *str, t_shell *shell)
{
	return (expand_env_impl(str, shell, false));
}

char	*expand_env_string_heredoc(char *str, t_shell *shell)
{
	return (expand_env_impl(str, shell, true));
}

char	*handle_env(t_shell *shell)
{
	if (!shell || !shell->input)
		return (NULL);
	return (expand_env_string(shell->input, shell));
}
