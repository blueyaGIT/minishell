/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalbano <dalbano@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 15:46:33 by dalbano           #+#    #+#             */
/*   Updated: 2025/03/31 15:03:20 by dalbano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_shell(t_shell *shell)
{
	if (shell && shell->input)
		ft_free_ptr(shell->input);
	// if (shell && shell->token_ll)
	// 	ft_free_token(&shell->token_ll, &ft_free_ptr);
	if (shell && shell->cmd_list)
		ft_free_command(&shell->cmd_list, &ft_free_ptr);
	if (shell && shell->cur_dir)
		ft_free_ptr(shell->cur_dir);
	if (shell && shell->old_dir)
		ft_free_ptr(shell->old_dir);
	if (shell && shell->env)
		ft_free_arr(shell->env);
	rl_clear_history();
}

t_shell	*get_shell(void)
{
	static t_shell	shell;
	return (&shell);
}