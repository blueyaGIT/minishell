/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_to_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalbano <dalbano@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 15:17:00 by dalbano           #+#    #+#             */
/*   Updated: 2025/04/11 15:26:37 by dalbano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*adding the tp of the tk with teh ENUM code*/
t_token_type	token_type(char *tk)
{
	if (!tk)
		return (WORD);
	if (!tk[0])
		return (WORD);
	if (ft_strcmp(tk, "|") == 0)
		return (PIPE);
	if (ft_strcmp(tk, "<") == 0)
		return (RI);
	if (ft_strcmp(tk, ">") == 0)
		return (RO);
	if (ft_strcmp(tk, "<<") == 0)
		return (HRD);
	if (ft_strcmp(tk, ">>") == 0)
		return (APD);
	if (tk[0] == '"' && tk[strlen(tk) - 1] == '"')
		return (DQT);
	if (tk[0] == '\'' && tk[strlen(tk) - 1] == '\'')
		return (SQT);
	return (WORD);
}

/**
	* @brief Converts an array of tokens into a linked 
	list with assigned ENUM types.
 *
 * This function iterates over the tokens array in the shell structure,
	allocates a new tk
 * structure for each tk,
	assigns the tk's tp based on its value via token_type(), and
 * appends it to the shell's linked list.
 *
 * @param shell Shell structure containing the tokens array and tk list.
 */
void	convert_tokens(t_shell *shell)
{
	t_token	*tmp_token;
	int		i;

	i = 0;
	if (!shell->tokens)
		return ;
	while (shell->tokens[i])
	{
		if (!shell->tokens[i])
			break ;
		tmp_token = ft_calloc(sizeof(t_token), 1);
		if (!tmp_token)
			return ;
		tmp_token->token_value = shell->tokens[i];
		tmp_token->tp = token_type(shell->tokens[i]);
		ft_lstadd_back(&shell->list, ft_lstnew((void *)tmp_token));
		i++;
	}
}

t_node	*create_new_node(void)
{
	t_node	*new_node;

	new_node = ft_calloc(sizeof(t_node), 1);
	if (!new_node)
		return (NULL);
	new_node->command = NULL;
	new_node->args = NULL;
	new_node->filename = NULL;
	new_node->redirections = NULL;
	new_node->next = NULL;
	return (new_node);
}

int	is_known_command(char *token_value)
{
	if (strcmp(token_value, "echo") == 0)
		return (1);
	if (strcmp(token_value, "ls") == 0)
		return (1);
	if (strcmp(token_value, "cat") == 0)
		return (1);
	if (strcmp(token_value, "pwd") == 0)
		return (1);
	return (0);
}

int	is_operator(char *token_value)
{
	if (strcmp(token_value, "<") == 0)
		return (1);
	if (strcmp(token_value, ">") == 0)
		return (1);
	if (strcmp(token_value, "<<") == 0)
		return (1);
	if (strcmp(token_value, ">>") == 0)
		return (1);
	if (strcmp(token_value, "|") == 0)
		return (1);
	return (0);
}
