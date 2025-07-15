/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalbano <dalbano@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 14:53:52 by lkloters          #+#    #+#             */
/*   Updated: 2025/07/15 15:32:31 by dalbano          ###   ########.fr       */
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

static char	*make_expansion(char *input, int *i, t_shell *shell)
{
	char	expansion_char;
	int		start;
	char	*result;

	expansion_char = input[*i];
	(*i)++;
	start = *i;
	if (expansion_char == '$')
		result = handle_dollar_exp(input, start, i, shell);
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
		if (input[i] == '$' || (input[i] == '~' && should_exp_tilde(input, i)))
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
