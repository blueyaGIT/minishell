/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkloters <lkloters@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 10:52:30 by lkloters          #+#    #+#             */
/*   Updated: 2025/07/09 10:43:47 by lkloters         ###   ########.fr       */
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
// t_command *parse_code(t_token *token)
// {
// 	t_command *command = NULL;
// 	command = malloc(sizeof(t_command));
// 	if (!valid_syntax(token))
// 		return (NULL);
// 	return (command);
// }