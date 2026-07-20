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
