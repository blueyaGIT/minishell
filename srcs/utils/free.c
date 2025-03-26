/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalbano <dalbano@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 14:48:05 by dalbano           #+#    #+#             */
/*   Updated: 2025/03/26 14:55:22 by dalbano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_io(t_redir *io)
{
	if (!io)
		return ;
	refresh_io(io);
	if (io->hrd_sep)
	{
		unlink(io->infile);
		ft_free_ptr(io->hrd_sep);
	}
	if (io->infile)
		ft_free_ptr(io->infile);
	if (io->outfile)
		ft_free_ptr(io->outfile);
	if (io)
		ft_free_ptr(io);
}

static void	delone_command(t_command *lst, void (*del)(void *))
{
	if (lst->command)
		(*del)(lst->command);
	if (lst->args)
		ft_free_arr(lst->args);
	if (lst->pipe_fd)
		(*del)(lst->pipe_fd);
	if (lst->io)
		ft_free_io(lst->io);
	(*del)(lst);
}

void	ft_free_command(t_command **lst, void (*del)(void *))
{
	t_command	*temp;

	temp = NULL;
	while (*lst != NULL)
	{
		temp = (*lst)->next;
		delone_command(*lst, del);
		*lst = temp;
	}
}
