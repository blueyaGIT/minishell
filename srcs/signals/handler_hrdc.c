/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_hrdc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalbano <dalbano@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:51:51 by dalbano           #+#    #+#             */
/*   Updated: 2025/03/12 17:02:36 by dalbano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_sigint_handler_heredoc()
{
	g_sig = 1;
	rl_done = 1;
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
	get_shell()->exit_code = 1;
}
