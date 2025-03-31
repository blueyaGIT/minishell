/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalbano <dalbano@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 15:04:44 by dalbano           #+#    #+#             */
/*   Updated: 2025/03/31 15:10:38 by dalbano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	process_input(t_shell *shell)
{
	char	*expanded_input;

	if (*(shell->input))
		add_history(shell->input);
	expanded_input = expand_variables(shell->input, shell->env,
			shell->last_exitcode);
	shell->input = expanded_input;
}

void handle_syntax_and_exit(t_shell *shell)
{
	run_syntax_checks(shell);
	shell->tokens = create_token(*shell);
	convert_tokens(shell);
	print_token_list(shell->list);
}

void	execute_commands(t_shell *shell)
{
	build_parsing_nodes(shell);
	print_node_list(shell->node);
	shell->cmd_list = convert_node_list_to_command_list(shell->node);
	print_command_list(shell->cmd_list);
	shell->list = NULL;
}
