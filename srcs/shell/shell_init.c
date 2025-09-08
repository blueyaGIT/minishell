/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalbano <dalbano@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 14:47:19 by dalbano           #+#    #+#             */
/*   Updated: 2025/09/08 14:47:20 by dalbano          ###   ########.fr       */
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
	return (SUCCESS);
}
