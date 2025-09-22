/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_io.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkloters <lkloters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 14:46:24 by dalbano           #+#    #+#             */
/*   Updated: 2025/09/22 17:12:57 by lkloters         ###   ########.fr       */
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
			// ft_printf(RED"ERROR: No such file or dir\n"RESET);
		return (false);
	}
	else if (io->outfile && io->fd_out == -1)
	{
		if (temp)
			ft_printf(RED"ERROR: No such file or dir\n"RESET);
		return (false);
	}
	return (true);
}
