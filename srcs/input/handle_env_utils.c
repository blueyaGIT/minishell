/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_env_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalbano <dalbano@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/20 00:00:00 by dalbano           #+#    #+#             */
/*   Updated: 2026/07/20 00:00:00 by dalbano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	should_exp_tilde(const char *s, int i)
{
	if (i > 0 && !ft_isspace((unsigned char)s[i - 1]))
		return (false);
	if (!s[i + 1] || s[i + 1] == '/' || ft_isspace((unsigned char)s[i + 1]))
		return (true);
	return (false);
}

static bool	is_env_blocked(char *input, int pos, bool ignore_quotes)
{
	int		i;
	bool	in_single_quotes;
	bool	in_double_quotes;
	bool	escaped;

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
	return (escaped || in_single_quotes);
}

bool	should_exp_env(char *input, int pos, bool ignore_quotes)
{
	if (!input || pos < 0 || input[pos] != '$')
		return (false);
	if (is_env_blocked(input, pos, ignore_quotes))
		return (false);
	if (pos + 1 >= (int)ft_strlen(input))
		return (false);
	if (!ft_isalnum(input[pos + 1]) && input[pos + 1] != '_'
		&& input[pos + 1] != '?')
		return (false);
	return (true);
}

char	*make_expansion(char *input, int *i, t_shell *shell)
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
