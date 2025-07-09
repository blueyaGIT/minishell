/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkloters <lkloters@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 10:52:30 by lkloters          #+#    #+#             */
/*   Updated: 2025/07/09 16:17:45 by lkloters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int process_and_execute_input(t_shell *shell)
{
	t_token *token;
	// t_command *command;
	
	token = lexer(shell->input);
	if(!token)
		return (1);
	if (!valid_syntax(token))
	{
		token->value = NULL;
		free_token(token);
		return (0);
	}
	shell->token = token;
	// command = parse_code(shell->token);
	// if (!command)
	// 	return (0);
	// shell->cmd_list = command;
	return (1);
}
// t_command *parse_code(t_token *token)
// {
// 	t_command *command = NULL;
	
// 	return (command);
// }