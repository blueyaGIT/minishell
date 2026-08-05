/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalbano <dalbano@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 14:43:39 by dalbano           #+#    #+#             */
/*   Updated: 2025/09/08 14:43:41 by dalbano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	print_echo_args(char **args)
{
	int	i;
	int	j;

	i = 0;
	while (args[i])
	{
		if (ft_printf("%s", args[i]) == -1)
			return (EXIT_FAILURE);
		if (args[i][0] != '\0')
		{
			j = i + 1;
			while (args[j] && args[j][0] == '\0')
				j++;
			if (args[j] != NULL && ft_printf(" ") == -1)
				return (EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

int	exec_echo(t_shell *shell, char **args)
{
	if (!args || !args[0])
		return (EXIT_SUCCESS);
	if (print_echo_args(args) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (!shell->cmd_list->is_echo_n && ft_printf("\n") == -1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
