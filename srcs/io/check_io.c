/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_io.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalbano <dalbano@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 14:46:24 by dalbano           #+#    #+#             */
/*   Updated: 2025/09/08 14:46:25 by dalbano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	check_io(t_redir *io, bool temp)
{
	if (!io || (!io->infile && !io->outfile))
		return (true);
	if (io->infile && io->fd_in == -1)
	{
		if (temp)
			ft_printf(RED"ERROR: No such file or dir\n"RESET);
		return (FAIL);
	}
	else if (io->outfile && io->fd_out == -1)
	{
		if (temp)
			ft_printf(RED"ERROR: No such file or dir\n"RESET);
		return (FAIL);
	}
	return (SUCCESS);
}
