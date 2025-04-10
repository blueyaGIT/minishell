/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalbano <dalbano@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 15:04:44 by dalbano           #+#    #+#             */
/*   Updated: 2025/04/10 13:52:33 by dalbano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	process_input(t_shell *shell)
{
	char *expanded;

	if (!shell->input)
		return;

	if (*(shell->input))
		add_history(shell->input);

	expanded = expand_variables(shell->input, shell->env, shell->last_exitcode);
	free(shell->input);
	shell->input = expanded;
}

void	handle_syntax_and_exit(t_shell *shell)
{
	if (run_syntax_checks(shell)) 
		return ;
	shell->tokens = create_token(*shell);
	if (!shell->tokens)  
	{
		shell->last_exitcode = 0;
		return ;
	}
	convert_tokens(shell);
	// printf("Prompt: %s\n", shell->input);
	// print_token_list(shell->list);
}
void	execute_commands(t_shell *shell)
{
	t_command	*cmd;

	build_parsing_nodes(shell);
	// print_node_list(shell->node);
	shell->cmd_list = convert_node_list_to_command_list(shell->node);
	// print_command_list(shell->cmd_list);
	cmd = shell->cmd_list;
	while (cmd)
	{
		if (check_redirections(cmd, shell))
			return ;
		cmd = cmd->next;
	}
	ft_lstfree(shell->list);
	shell->list = NULL;
}
