/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalbano <dalbano@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 14:48:05 by dalbano           #+#    #+#             */
/*   Updated: 2025/04/07 16:07:04 by dalbano          ###   ########.fr       */
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
		// ft_free_ptr(io->hrd_sep);
	}
	// if (io->infile)
	// 	ft_free_ptr(io->infile);
	// if (io->outfile)
	// 	ft_free_ptr(io->outfile);
	// if (io)
	// 	ft_free_ptr(io);
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

void ft_free_nodes(t_node *head)
{
    t_node *temp;
    int i;

    while (head)
    {
        temp = head;
        head = head->next;
        
        if (temp->command)
            free(temp->command);
        if (temp->args)
            free(temp->args);
        
        if (temp->filename)
        {
            for (i = 0; temp->filename[i] != NULL; i++)
                free(temp->filename[i]);
            free(temp->filename);
        }
        
        if (temp->redirections)
        {
            for (i = 0; temp->redirections[i] != NULL; i++)
                free(temp->redirections[i]);
            free(temp->redirections);
        }
        
        free(temp);
    }
}
