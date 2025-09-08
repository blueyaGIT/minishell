/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalbano <dalbano@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 14:46:23 by dalbano           #+#    #+#             */
/*   Updated: 2025/09/08 14:46:24 by dalbano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

static bool	valid_unset_usage(const char *input)
{
	int		i;

	if (!input)
		return (false);
	i = 0;
	while (input[i] && ft_isspace(input[i]))
		i++;
	if (ft_strncmp(input, "unset", 5) == 0)
	{
		i += 5;
		while (input[i] && ft_isspace(input[i]))
			i++;
		if (input[i] == '$')
			return (false);
		if (!is_valid_varname((char *)&input[i]))
			return (false);
	}
	return (true);
}

bool	valid_input(const char *input)
{
	if (!valid_quotes(input))
		return (ft_printf("minishell: syntax error: unclosed quote\n"), 0);
	if (!valid_escape_chars(input))
		return (ft_printf("minishell: syntax error: invalid backslash\n"), 0);
	if (!valid_unset_usage(input))
		return (0);
	return (true);
}
