/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalbano <dalbano@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 10:52:30 by lkloters          #+#    #+#             */
/*   Updated: 2025/07/08 13:29:32 by dalbano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int process_and_execute_input(t_shell *shell)
{
    t_token *token;

    token = lexer(shell->input);
    if (!token)
        return 0;
    shell->token = token;
    return 1;
}
t_command *parse_code(t_token *token)
{
	t_command *cmd;
	int arg_count;
	cmd = malloc(sizeof(t_command));
	cmd->args = 0;
	arg_count = count_arguments(token);
	cmd->args = (char **)malloc(sizeof(char *) * (arg_count + 1));
	while (token)
}