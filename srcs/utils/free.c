/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalbano <dalbano@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 14:47:30 by dalbano           #+#    #+#             */
/*   Updated: 2025/09/08 14:47:31 by dalbano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_io(t_redir *io)
{
	if (!io)
		return ;
	refresh_io(io);
	if (io && io->outfile)
		free(io->outfile);
	if (io && io->infile)
		free(io->infile);
	if (io && io->hrd_del)
		free(io->hrd_del);
	if (io)
		ft_free_ptr(io);
}

void	ft_free_env(char **env)
{
	int	i;

	i = 0;
	if (env)
	{
		while (env[i])
		{
			ft_free_ptr(env[i]);
			i++;
		}
		free(env);
		env = NULL;
	}
}

void	help_free(t_command *cmd)
{
	if (cmd->cmd)
		free(cmd->cmd);
	if (cmd->cpath)
		free(cmd->cpath);
	if (cmd->filename)
	{
		free(cmd->filename);
		cmd->filename = NULL;
	}
}

void	ft_free_command(t_command *cmd)
{
	int	i;

	i = 0;
	if (!cmd)
		return ;
	help_free(cmd);
	if (cmd->args)
	{
		while (cmd->args[i])
		{
			free(cmd->args[i]);
			i++;
		}
		free(cmd->args);
	}
	if (cmd->pipe_fd)
		free(cmd->pipe_fd);
	ft_free_io(cmd->io);
	free(cmd);
}

void	free_token(t_token *token)
{
	t_token	*tmp;

	while (token)
	{
		tmp = token->next;
		if (token->value)
		{
			free(token->value);
			token->value = NULL;
		}
		free(token);
		token = tmp;
	}
}
