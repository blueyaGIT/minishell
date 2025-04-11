/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalbano <dalbano@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 15:18:53 by dalbano           #+#    #+#             */
/*   Updated: 2025/04/11 15:35:55 by dalbano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_command_fields(t_command *cmd, t_node *node)
{
	cmd->command = NULL;
	cmd->filename = NULL;
	if (node->command)
		cmd->command = ft_strdup(node->command);
	if (node->filename && node->filename[0])
		cmd->filename = ft_strdup(node->filename[0]);
	cmd->args = split_args(node->args);
	cmd->io->infile = NULL;
	cmd->io->outfile = NULL;
	cmd->io->hrd_sep = NULL;
	cmd->io->hrd_flag = false;
}

void	fill_redirections(t_command *cmd, t_node *node)
{
	int	i;

	i = -1;
	while (node && node->rds && node->rds[++i])
	{
		if (ft_strcmp(node->rds[i], "<") == 0)
		{
			if (node->filename && node->filename[i])
				cmd->io->infile = ft_strdup(node->filename[i]);
		}
		else if (ft_strcmp(node->rds[i], ">") == 0
			|| ft_strcmp(node->rds[i], ">>") == 0)
		{
			if (node->filename && node->filename[i])
				cmd->io->outfile = ft_strdup(node->filename[i]);
		}
		else if (ft_strcmp(node->rds[i], "<<") == 0)
		{
			if (node->filename && node->filename[i])
			{
				cmd->io->hrd_sep = ft_strdup(node->filename[i]);
				cmd->io->hrd_flag = true;
			}
		}
	}
}

static void	update_command_and_move(t_node **node, t_command **prev,
		t_command **head, t_command *curr)
{
	curr->prev = *prev;
	if ((*node)->command)
		curr->command = ft_strdup((*node)->command);
	if ((*node)->filename && (*node)->filename[0])
		curr->filename = ft_strdup((*node)->filename[0]);
	if ((*node)->args)
		curr->args = split_args((*node)->args);
	fill_redirections(curr, *node);
	if ((*node)->next)
		curr->pipe_flag = true;
	if (*prev)
		(*prev)->next = curr;
	else
		*head = curr;
	*prev = curr;
	*node = (*node)->next;
}

t_command	*convert_node_list_to_command_list(t_node *node)
{
	t_command	*head;
	t_command	*prev;
	t_command	*curr;

	head = NULL;
	prev = NULL;
	while (node)
	{
		curr = ft_calloc(sizeof(t_command), 1);
		if (!curr)
			return (NULL);
		curr->io = ft_calloc(sizeof(t_redir), 1);
		if (!curr->io)
		{
			free(curr);
			return (NULL);
		}
		update_command_and_move(&node, &prev, &head, curr);
	}
	return (head);
}

char	**split_args(char *args)
{
	char	**res;
	int		i;
	int		p;
	int		s;

	i = 0;
	p = 0;
	res = ft_calloc(sizeof(char *), (count_words(args) + 1));
	if (!res)
		return (NULL);
	while (args[p])
	{
		while (args[p] == ' ')
			p++;
		if (args[p])
		{
			s = p;
			while (args[p] && args[p] != ' ')
				p++;
			res[i] = ft_substr(args, s, p - s);
			i++;
		}
	}
	res[i] = NULL;
	return (res);
}
