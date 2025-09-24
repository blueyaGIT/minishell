/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalbano <dalbano@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 14:47:02 by dalbano           #+#    #+#             */
/*   Updated: 2025/09/24 17:44:28 by dalbano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static void print_tokens(t_token *head)
// {
//     t_token *current = head;
//     int index = 0;

//     printf("------ TOKEN LIST ------\n");
//     while (current)
//     {
//         printf("Token[%d]:\n", index);
//         printf("  value      : %s\n", current->value ? current->value : "NULL");
//         printf("  type       : %d\n", current->type);
//         printf("  is_echo    : %s\n", current->is_echo ? "true" : "false");
//         printf("  is_echo_n  : %s\n", current->is_echo_n ? "true" : "false");
//         printf("  is_removed : %s\n", current->is_removed ? "true" : "false");
//         printf("  add_space  : %s\n", current->add_space ? "true" : "false");
//         printf("  next       : %p\n", (void *)current->next);
//         printf("  prev       : %p\n", (void *)current->prev);
//         printf("------------------------\n");

//         current = current->next;
//         index++;
//     }
// }

static t_token *create_pipe_token(void)
{
    t_token *pipe = malloc(sizeof(t_token));
    if (!pipe)
        return NULL;
    pipe->value = ft_strdup("|");
    if (!pipe->value)
    {
        free(pipe);
        return NULL;
    }
    pipe->type = T_PIPE;
    pipe->is_echo = 0;
    pipe->is_echo_n = 0;
    pipe->is_removed = 0;
    pipe->add_space = 0;
    pipe->next = NULL;
    pipe->prev = NULL;
    return pipe;
}

static t_token *create_cat_token(void)
{
    t_token *cat = malloc(sizeof(t_token));
    if (!cat)
        return NULL;
    cat->value = ft_strdup("cat");
    if (!cat->value)
    {
        free(cat);
        return NULL;
    }
    cat->type = 7;
    cat->is_echo = 0;
    cat->is_echo_n = 0;
    cat->is_removed = 0;
    cat->add_space = 0;
    cat->next = NULL;
    cat->prev = NULL;
    return cat;
}


static int insert_pipe(t_token *token)
{
    t_token *current = token;
    int first_is_cat = (token && token->type == 7 && token->value && ft_strcmp(token->value, "cat") == 0);

    while (current && current->next && current->next->next)
    {
        if (current->type == T_HEREDOC &&
            current->next->type == HEREDOC_DELIM && current->next->next->type != T_PIPE)
        {
            t_token *pipe = create_pipe_token();
            if (!pipe)
                return (0);

            t_token *next_token = current->next->next;
            pipe->prev = current->next;
            pipe->next = next_token;
            current->next->next = pipe;
            if (next_token)
                next_token->prev = pipe;
            if (first_is_cat)
            {
                t_token *cat = create_cat_token();
                if (!cat)
                {
                    free(pipe);
                    return (0);
                }
                cat->prev = pipe;
                cat->next = next_token;
                pipe->next = cat;
                if (next_token)
                    next_token->prev = cat;
            }
            current = next_token;
        }
        else
            current = current->next;
    }
    return (1);
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
	insert_pipe(token);
	
	// print_tokens(token);
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

