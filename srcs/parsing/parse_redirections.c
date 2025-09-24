/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalbano <dalbano@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 14:46:57 by dalbano           #+#    #+#             */
/*   Updated: 2025/09/24 17:56:57 by dalbano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_output_redirection(t_token *token, t_command *current)
{
	t_redir_file	*new_file;

	new_file = new_redir_file(current->filename, token->type);
	if (!new_file)
		return ;
	add_redir_file(&current->io->outfiles, new_file);
	current->io->hrd_sep = token->type;
}

static void	handle_input_and_heredoc(t_token *token, t_command *current)
{
	t_redir_file	*new_file;

	if (token->type == T_REDIR_IN)
	{
		new_file = new_redir_file(current->filename, token->type);
		if (!new_file)
			return ;
		add_redir_file(&current->io->infiles, new_file);
		current->io->hrd_sep = token->type;
	}
	else if (token->type == T_HEREDOC)
	{
		if (!current->cmd)
		{
			current->cmd = ft_strdup("HRD");
			if (!current->cmd)
				return ;
		}
		if (current->io->hrd_del)
			free(current->io->hrd_del);
		current->io->hrd_del = ft_strdup(current->filename);
		current->io->hrd_flag = true;
		current->io->hrd_sep = token->type;
	}
}

static void	redirection_to_command(t_token *token, t_command *current)
{
	if (token->type == T_REDIR_OUT || token->type == T_APPEND)
		handle_output_redirection(token, current);
	else
		handle_input_and_heredoc(token, current);
}

t_token	*handle_redirection(t_token *token, t_command **command)
{
	t_command	*current;

	if (!*command)
		command_add_back(command, new_command());
	current = command_last(*command);
	if (!current)
		return (NULL);
	init_redir(current);
	if (token->next && (token->next->type == FILENAME
			|| token->next->type == HEREDOC_DELIM) && token->next->value)
	{
		if (current->filename)
		{
			free(current->filename);
			current->filename = NULL;
		}
		current->filename = ft_strdup(token->next->value);
		if (!current->filename)
			return (NULL);
		redirection_to_command(token, current);
	}
	token = token->next;
	return (token->next);
}
