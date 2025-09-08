/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalbano <dalbano@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 14:47:26 by dalbano           #+#    #+#             */
/*   Updated: 2025/09/08 14:47:27 by dalbano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_command_list(t_command *cmd_list)
{
	t_command	*current;
	t_command	*temp;

	if (!cmd_list)
		return ;
	kill_pipes(cmd_list, NULL);
	current = cmd_list;
	while (current->prev)
		current = current->prev;
	while (current)
	{
		temp = current->next;
		ft_free_command(current);
		current = temp;
	}
}

void	reload_shell(t_shell *shell)
{
	if (shell && shell->input)
	{
		free(shell->input);
		shell->input = NULL;
	}
	if (shell && shell->token)
	{
		free_token(shell->token);
		shell->token = NULL;
	}
	if (shell && shell->tokens)
	{
		ft_free_arr(shell->tokens);
		shell->tokens = NULL;
	}
	if (shell && shell->cmd_list)
	{
		free_command_list(shell->cmd_list);
		shell->cmd_list = NULL;
	}
}

void	ft_free_tok(t_shell *shell)
{
	if (shell && shell->token)
	{
		free_token(shell->token);
		shell->token = NULL;
	}
	if (shell && shell->tokens)
	{
		ft_free_arr(shell->tokens);
		shell->tokens = NULL;
	}
}

void	ft_free_shell(t_shell *shell)
{
	if (shell && shell->input)
	{
		free(shell->input);
		shell->input = NULL;
	}
	ft_free_tok(shell);
	if (shell && shell->cmd_list)
	{
		free_command_list(shell->cmd_list);
		shell->cmd_list = NULL;
	}
	if (shell && shell->env)
	{
		ft_free_env(shell->env);
		shell->env = NULL;
	}
	rl_clear_history();
}

t_shell	*get_shell(void)
{
	static t_shell	shell;

	return (&shell);
}
