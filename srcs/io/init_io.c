/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_io.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalbano <dalbano@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 14:46:28 by dalbano           #+#    #+#             */
/*   Updated: 2025/09/24 17:56:57 by dalbano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redir_file	*new_redir_file(char *filename, t_token_type type)
{
	t_redir_file	*new_file;

	new_file = malloc(sizeof(t_redir_file));
	if (!new_file)
		return (NULL);
	new_file->filename = ft_strdup(filename);
	if (!new_file->filename)
	{
		free(new_file);
		return (NULL);
	}
	new_file->type = type;
	new_file->next = NULL;
	return (new_file);
}

void	add_redir_file(t_redir_file **list, t_redir_file *new_file)
{
	t_redir_file	*current;

	if (!list || !new_file)
		return ;
	if (!*list)
	{
		*list = new_file;
		return ;
	}
	current = *list;
	while (current->next)
		current = current->next;
	current->next = new_file;
}

void	free_redir_files(t_redir_file *list)
{
	t_redir_file	*temp;

	while (list)
	{
		temp = list;
		list = list->next;
		if (temp->filename)
			free(temp->filename);
		free(temp);
	}
}

void	init_redir(t_command *cmd)
{
	if (!cmd->io)
	{
		cmd->io = malloc(sizeof * cmd->io);
		if (!cmd->io)
			return ;
		cmd->io->infiles = NULL;
		cmd->io->outfiles = NULL;
		cmd->io->hrd_del = NULL;
		cmd->io->hrd_flag = false;
		cmd->io->fd_in = -1;
		cmd->io->fd_out = -1;
		cmd->io->stdin_backup = -1;
		cmd->io->stdout_backup = -1;
	}
}
