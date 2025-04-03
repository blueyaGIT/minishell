/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalbano <dalbano@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 15:04:44 by dalbano           #+#    #+#             */
/*   Updated: 2025/04/03 14:14:24 by dalbano          ###   ########.fr       */
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
	free(shell->input);
	shell->input = expanded_input;
}

void	handle_syntax_and_exit(t_shell *shell)
{
	char	*expanded;

	run_syntax_checks(shell);
	expanded = expand_variables(shell->input, shell->env, shell->last_exitcode);
	free(shell->input);
	shell->input = expanded;
	shell->tokens = create_token(*shell);
	printf("Prompt: %s\n", shell->input);
	convert_tokens(shell);
	print_token_list(shell->list);
}

void	execute_commands(t_shell *shell)
{
	build_parsing_nodes(shell);

	print_node_list(shell->node);
	shell->cmd_list = convert_node_list_to_command_list(shell->node);
	print_command_list(shell->cmd_list);
	ft_lstfree(shell->list);
	shell->list = NULL;
	// free(shell->input);
}
