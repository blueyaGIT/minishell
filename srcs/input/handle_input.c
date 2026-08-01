/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkloters <lkloters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 14:46:18 by dalbano           #+#    #+#             */
/*   Updated: 2025/09/12 12:07:46 by lkloters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	process_input_char(const char *input, size_t *i, char *result,
		size_t *j)
{
	char	quote;

	if (input[*i] == '\'' || input[*i] == '\"')
	{
		quote = input[(*i)++];
		while (*i < ft_strlen(input) && input[*i] != quote)
			result[(*j)++] = input[(*i)++];
		if (*i < ft_strlen(input))
			(*i)++;
	}
	else
		result[(*j)++] = input[(*i)++];
}

char	*remove_quotes(const char *input)
{
	char		*result;
	size_t		i;
	size_t		j;

	if (!input)
		return (NULL);
	result = (char *)malloc(sizeof(char) * (ft_strlen(input) + 1));
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (i < ft_strlen(input))
		process_input_char(input, &i, result, &j);
	result[j] = '\0';
	return (result);
}

char	*handle_input(char *input, t_shell *shell)
{
	char	*result;

	if (!valid_input(input))
		return (NULL);
	result = handle_env(shell);
	if (!result)
		return (NULL);
	return (result);
}
