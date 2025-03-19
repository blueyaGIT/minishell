/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_nrml.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalbano <dalbano@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:51:25 by dalbano           #+#    #+#             */
/*   Updated: 2025/03/19 13:30:23 by dalbano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Signal handler for Ctrl+C in normal shell mode
 * 
 * - Moves to newline, clears current input and refreshes readline prompt
 * @note This does not exit the shell but resets the prompt display.
 */
void	ft_sigint_handler_normal(int signbr)
{
	(void)signbr;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}
