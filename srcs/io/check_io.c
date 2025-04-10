/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_io.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalbano <dalbano@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 16:27:04 by dalbano           #+#    #+#             */
/*   Updated: 2025/04/10 14:41:14 by dalbano          ###   ########.fr       */
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
			printf(RED"ERROR: No such file or dir\n"RESET);
		return (FAIL);
	}
	else if (io->outfile && io->fd_out == -1)
	{
		if (temp)
			printf(RED"ERROR: No such file or dir\n"RESET);
		return (FAIL);
	}
	return (SUCCESS);
}
