/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_io.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalbano <dalbano@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 14:46:24 by dalbano           #+#    #+#             */
/*   Updated: 2025/09/24 17:56:57 by dalbano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	check_io(t_redir *io, bool temp)
{
	if (!io || (!io->infiles && !io->outfiles))
		return (true);
	if (io->infiles && io->fd_in == -1)
	{
		if (temp)
			ft_printf(RED"ERROR: No such file or dir\n"RESET);
		return (false);
	}
	else if (io->outfiles && io->fd_out == -1)
	{
		if (temp)
			ft_printf(RED"ERROR: No such file or dir\n"RESET);
		return (false);
	}
	return (true);
}
