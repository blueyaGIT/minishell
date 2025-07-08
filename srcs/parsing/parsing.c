/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkloters <lkloters@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 10:52:30 by lkloters          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/07/05 14:12:42 by lkloters         ###   ########.fr       */
=======
/*   Updated: 2025/07/04 14:56:37 by dalbano          ###   ########.fr       */
>>>>>>> 4aae29301e4a46862f1da7dbbe1a2ce1f86e7892
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int process_and_execute_input(t_shell *shell)
{
<<<<<<< HEAD
    t_token *token;

    token = lexer(shell->input);
    if (!token)
        return 0;
    shell->token = token;
    return 1;
=======
	t_token *token;
	
	token = lexer(shell->input);
	if(!token)
		return (0);
	shell->token = token;
	return (0);
>>>>>>> 4aae29301e4a46862f1da7dbbe1a2ce1f86e7892
}
t_command *parse_code(t_token *token)
{
	t_command *command = NULL;
	command = malloc(sizeof(t_command));
	if (!valid_syntax(token))
		return (NULL);
	fill_commands(token, command)
}