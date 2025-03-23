/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalbano <dalbano@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 17:32:03 by dalbano           #+#    #+#             */
/*   Updated: 2025/03/23 12:26:54 by dalbano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	shell_init(t_shell *shell, char **envp)
{
	shell->env = gc_arr_cpy(envp);
	if (!shell->env)
		return (-1);
	// if (env_init(&shell->env) == fail)
	// {
	// 	gc_free_arr(shell->env);
	// 	return (-1);
	// }
	shell->has_error = false;
	shell->exit_code = 0;
	return (0);	
}
