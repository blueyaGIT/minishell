/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalbano <dalbano@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 15:05:28 by dalbano           #+#    #+#             */
/*   Updated: 2025/04/12 15:23:44 by dalbano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_flag(char **args)
{
	if (ft_strcmp(args[0], "-n") == 0)
		return (1);
	return (0);
}

int	exec_echo(char **args)
{
	int	i;
	int	status;

	i = check_flag(args);
	status = 0;
	while (args[i])
	{
		if (status == -1)
			return (EXIT_FAILURE);
		status = ft_printf(args[i], 1);
		if (status == -1)
			return (EXIT_FAILURE);
		i++;
	}
	if (check_flag(args) == 0)
		status = ft_printf("\n", 1);
	if (status == -1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
