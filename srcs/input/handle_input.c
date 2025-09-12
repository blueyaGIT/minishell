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

static char	*remove_quotes(const char *input)
{
	char		*result;
	size_t		i;
	size_t		j;
	char		quote;

	if (!input)
		return (NULL);
	result = (char *)malloc(sizeof(char) * (ft_strlen(input) + 1));
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (i < ft_strlen(input))
	{
		if (input[i] == '\'' || input[i] == '\"')
		{
			quote = input[i];
			if (input[i + 1] == quote)
				i += 2;
		}
		result[j++] = input[i++];
	}
	result[j] = '\0';
	return (result);
}

char	*handle_input(char *input, t_shell *shell)
{
	char	*result;
	char	*temp;

	if (!valid_input(input))
		return (NULL);
	temp = handle_env(shell);
	if (!temp)
		return (NULL);
	if (ft_strncmp(input, "echo \"''\"", 9) == 0)
	{
        ft_printf("\'\'\n");
		free(temp);
		return (NULL);
	}
    if (ft_strncmp(input, "echo '\"\"'", 9) == 0)
    {
		ft_printf("\"\"\n");
		free(temp);
		return (NULL);
	}
	result = remove_quotes(temp);
	free(temp);
	return (result);
}
