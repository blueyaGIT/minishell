/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalbano <dalbano@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 10:52:30 by lkloters          #+#    #+#             */
/*   Updated: 2025/07/04 14:56:37 by dalbano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int process_and_execute_input(t_shell *shell)
{
	t_token *token;
	
	token = lexer(shell->input);
	if(!token)
		return (0);
	shell->token = token;
	return (0);
}
