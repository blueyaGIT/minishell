/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalbano <dalbano@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 15:04:32 by dalbano           #+#    #+#             */
/*   Updated: 2025/04/11 15:04:41 by dalbano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*replace_env_var(char *input, char **env, int lastexitcode)
{
	char	*var_name;
	char	*value;
	char	*exit_code_str;

	if (!input || input[0] != '$')
		return (ft_strdup(input));
	if (strcmp(input, "$?") == 0)
	{
		exit_code_str = malloc(12);
		if (!exit_code_str)
			return (NULL);
		sprintf(exit_code_str, "%d", lastexitcode);
		return (exit_code_str);
	}
	var_name = input + 1;
	value = get_env_value(var_name, env);
	if (value)
		return (value);
	else
		return (ft_strdup(""));
}

char	*extract_var_name(char *input)
{
	int	i;

	i = 0;
	if (!input || !input[i] || !(ft_isalpha(input[i]) || input[i] == '_'))
		return (ft_strdup(""));
	while (input[i] && (ft_isalnum(input[i]) || input[i] == '_'))
		i++;
	return (strndup(input, i));
}

void	int_to_str(int num, char *str)
{
	int	i;
	int	temp;
	int	length;

	i = 0;
	if (num == 0)
		str[i++] = '0';
	else
	{
		temp = num;
		length = 0;
		while (temp != 0)
		{
			temp /= 10;
			length++;
		}
		str[length] = '\0';
		while (num != 0)
		{
			str[--length] = (num % 10) + '0';
			num /= 10;
		}
	}
}
