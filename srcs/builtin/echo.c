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

int	exec_echo(t_shell *shell, char **args)
{
	int	i;

	i = 0;
	if (!args[0])
		return (EXIT_SUCCESS);
	while (args[i])
	{
		if (ft_printf("%s", args[i]) == -1)
			return (EXIT_FAILURE);
		if (args[i + 1])
		{
			if (ft_printf(" ") == -1)
				return (EXIT_FAILURE);
		}
		i++;
	}
	if (!shell->cmd_list->is_echo_n)
	{
		if (ft_printf("\n") == -1)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
