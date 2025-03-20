/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalbano <dalbano@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 16:24:33 by dalbano           #+#    #+#             */
/*   Updated: 2025/03/20 16:37:42 by dalbano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dbmsg(char *str)
{
	if (DEBUG)
	{
		ft_putstr_fd(BOLD, STDERR_FILENO);
		ft_putstr_fd(ITALIC, STDERR_FILENO);
		ft_putstr_fd(LIGHT_PINK, STDERR_FILENO);
		ft_putstr_fd("DEBUG", STDERR_FILENO);
		ft_putstr_fd(RESET, STDERR_FILENO);
		ft_putstr_fd(" > ", STDERR_FILENO);
		ft_putstr_fd(LIGHT_PINK, STDERR_FILENO);
		if (str)
			ft_putendl_fd(str, STDERR_FILENO);
		ft_putstr_fd(RESET, STDERR_FILENO);
	}
}
