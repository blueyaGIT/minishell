/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalbano <dalbano@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 15:04:44 by dalbano           #+#    #+#             */
/*   Updated: 2025/04/24 17:20:00 by dalbano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	process_input(t_shell *shell)
{
	char	*expanded;

	if (shell->input == NULL)
		exec_exit(shell, NULL);
	else if (!*shell->input)
		return (true);
	add_history(shell->input);
	expanded = expand_variables(shell->input, shell->env, shell->last_exitcode);
	if (!expanded)
		return (false);
	// free(shell->input);
	shell->input = expanded;
	return (true);
}

bool	handle_syntax_and_exit(t_shell *shell)
{
	if (run_syntax_checks(shell))
		return (false);
	shell->tokens = create_token(*shell);
	if (!shell->tokens)
	{
		shell->last_exitcode = 0;
		return (false);
	}
	convert_tokens(shell);
	return (true);
}

bool	execute_commands(t_shell *shell)
{
	t_command	*cmd;

	build_parsing_nodes(shell);
	shell->cmd_list = convert_node_list_to_command_list(shell->node);
	cmd = shell->cmd_list;
	while (cmd)
	{
		if (check_redirections(cmd, shell))
			return (false);
		cmd = cmd->next;
	}
	ft_lstfree(shell->list);
	shell->list = NULL;
	return (true);
}

bool	process_and_execute_input(t_shell *shell)
{
	if (!process_input(shell))
		return (false);
	if (!handle_syntax_and_exit(shell))
		return (false);
	if (!execute_commands(shell))
		return (false);
	return (true);
}
