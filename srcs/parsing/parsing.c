/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalbano <dalbano@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 14:47:02 by dalbano           #+#    #+#             */
/*   Updated: 2025/09/08 15:06:47 by dalbano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	process_and_execute_input(t_shell *shell)
{
	t_token		*token;
	t_command	*command;

	token = lexer(shell->input, shell);
	if (!token)
		return (0);
	if (!valid_syntax(token))
	{
		free_token(token);
		return (0);
	}
	shell->token = token;
	command = parse_code(shell->token);
	if (!command && shell->token)
	{
		free_token(shell->token);
		shell->token = NULL;
		return (0);
	}
	shell->cmd_list = command;
	return (1);
}

t_command	*parse_code(t_token *token)
{
	t_command	*command;

	command = NULL;
	while (token)
	{
		if (token->type == T_PIPE)
			token = handle_pipe(token, &command);
		else if (is_redirection_token(token))
			token = handle_redirection(token, &command);
		else if (is_word(token->type))
			token = handle_word(token, &command);
		else
			return (NULL);
	}
	return (command);
}
