/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalbano <dalbano@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 14:48:05 by dalbano           #+#    #+#             */
/*   Updated: 2025/04/09 16:42:11 by dalbano          ###   ########.fr       */
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

// static void	delone_command(t_command *lst, void (*del)(void *))
// {
// 	if (lst->command)
// 		(*del)(lst->command);
// 	if (lst->args)
// 		ft_free_arr(lst->args);
// 	if (lst->pipe_fd)
// 		(*del)(lst->pipe_fd);
// 	if (lst->io)
// 		ft_free_io(lst->io);
// 	(*del)(lst);
// }

void	ft_free_command(t_command *cmd)
{
	int	i;

	i = 0;
	if (!cmd)
		return ;
	free(cmd->command);
	free(cmd->cpath);
	free(cmd->filename);
	if (cmd->args)
	{
		while (cmd->args[i])
		{
			free(cmd->args[i]);
			i++;
		}
		free(cmd->args);
	}
	free(cmd->pipe_fd);
	ft_free_io(cmd->io);
	free(cmd);
}

void	ft_free_tokens(t_token **lst)
{
	t_token	*tmp;

	while (*lst)
	{
		tmp = (*lst)->next;
		if ((*lst)->token_value)
			free((*lst)->token_value);
		free(*lst);
		*lst = tmp;
	}
}

void	ft_free_nodes(t_node *head)
{
	t_node	*temp;

	while (head)
	{
		temp = head;
		head = head->next;
		if (temp->command)
			free(temp->command);
		if (temp->args)
			free(temp->args);
		if (temp->filename)
			ft_free_arr(temp->filename);
		if (temp->redirections)
			ft_free_arr(temp->redirections);
		free(temp);
	}
}
