/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kill_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalbano <dalbano@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 16:21:36 by dalbano           #+#    #+#             */
/*   Updated: 2025/03/31 15:02:47 by dalbano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	kill_shell(t_shell *shell, int ecode)
{
	if (shell)
	{
		if (shell->cmd_list && shell->cmd_list->io)
			kill_fds(shell->cmd_list, true);
		ft_free_shell(shell);
	}
	exit(ecode);
}
