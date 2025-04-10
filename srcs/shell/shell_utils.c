/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalbano <dalbano@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 15:46:33 by dalbano           #+#    #+#             */
/*   Updated: 2025/04/10 14:34:00 by dalbano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	reload_shell(t_shell *shell)
{
	if (shell && shell->input)
	{
		free(shell->input);
		shell->input = NULL;
	}
	if (shell && shell->tokens)
		ft_free_arr(shell->tokens);
	if (shell && shell->node)
		ft_free_nodes(shell->node);
	if (shell && shell->list)
		ft_lstfree(shell->list);
	if (shell && shell->cmd_list)
		ft_free_command(shell->cmd_list);
}

void	ft_free_shell(t_shell *shell)
{
	if (shell && shell->input)
	{
		free(shell->input);
		shell->input = NULL;
	}
	if (shell && shell->tokens)
		ft_free_arr(shell->tokens);
	if (shell && shell->node)
		ft_free_nodes(shell->node);
	if (shell && shell->list)
		ft_lstfree(shell->list);
	if (shell && shell->cmd_list)
		ft_free_command(shell->cmd_list);
	if (shell && shell->cur_dir)
		ft_free_ptr(shell->cur_dir);
	if (shell && shell->old_dir)
		ft_free_ptr(shell->old_dir);
	if (shell && shell->env)
		ft_free_env(shell->env);
	rl_clear_history();
}

t_shell	*get_shell(void)
{
	static t_shell	shell;

	return (&shell);
}
