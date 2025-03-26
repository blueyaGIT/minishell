/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kill_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalbano <dalbano@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 16:21:36 by dalbano           #+#    #+#             */
/*   Updated: 2025/03/26 14:57:13 by dalbano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	kill_shell(t_shell *shell, int ecode)
{
	if (shell)
	{
		if (shell->command_ll && shell->command_ll->io)
			kill_fds(shell->command_ll, true);
		ft_free_shell(shell);
	}
	exit(ecode);
}
