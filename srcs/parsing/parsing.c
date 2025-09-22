/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkloters <lkloters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 14:47:02 by dalbano           #+#    #+#             */
/*   Updated: 2025/09/22 15:30:16 by lkloters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void print_tokens(t_token *head)
{
    t_token *current = head;
    int index = 0;

    printf("------ TOKEN LIST ------\n");
    while (current)
    {
        printf("Token[%d]:\n", index);
        printf("  value      : %s\n", current->value ? current->value : "NULL");
        printf("  type       : %d\n", current->type);
        printf("  is_echo    : %s\n", current->is_echo ? "true" : "false");
        printf("  is_echo_n  : %s\n", current->is_echo_n ? "true" : "false");
        printf("  is_removed : %s\n", current->is_removed ? "true" : "false");
        printf("  add_space  : %s\n", current->add_space ? "true" : "false");
        printf("  next       : %p\n", (void *)current->next);
        printf("  prev       : %p\n", (void *)current->prev);
        printf("------------------------\n");

        current = current->next;
        index++;
    }
}


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
	print_tokens(token);
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
