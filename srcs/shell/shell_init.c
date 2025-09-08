/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkloters <lkloters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 14:47:19 by dalbano           #+#    #+#             */
/*   Updated: 2025/09/08 14:54:45 by lkloters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	shell_init(t_shell *shell, char **envp)
{
	env_init(shell, envp);
	shell->cmd_list = NULL;
	shell->pid = -1;
	shell->has_error = false;
	shell->last_exitcode = 0;
	shell->amount_here = 0;
	return (true);
}
