/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalbano <dalbano@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 15:22:47 by dalbano           #+#    #+#             */
/*   Updated: 2025/04/11 15:26:47 by dalbano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	process_word_token(t_node *new_node, t_list **token_lst,
		bool *prev_was_redirect)
{
	t_token	*tk;
	char	*temp;

	tk = (t_token *)(*token_lst)->content;
	if (*prev_was_redirect)
	{
		new_node->filename = ft_add_to_array(new_node->filename,
				tk->token_value);
		*prev_was_redirect = false;
	}
	else if (!new_node->command)
		new_node->command = ft_strdup(tk->token_value);
	else
	{
		if (!new_node->args)
			new_node->args = ft_strdup(tk->token_value);
		else
		{
			temp = ft_strjoin(new_node->args, " ");
			free(new_node->args);
			new_node->args = ft_strjoin(temp, tk->token_value);
			free(temp);
		}
	}
	*token_lst = (*token_lst)->next;
}

char	**ft_add_to_array(char **array, char *new_entry)
{
	int		len;
	char	**new_array;

	len = 0;
	while (array && array[len])
		len++;
	new_array = ft_calloc((len + 2), sizeof(char *));
	if (!new_array)
		return (NULL);
	if (array)
		ft_memcpy(new_array, array, len * sizeof(char *));
	new_array[len] = ft_strdup(new_entry);
	new_array[len + 1] = NULL;
	free(array);
	return (new_array);
}

void	process_redirection_token(t_node *new_node, t_list **token_lst)
{
	t_token	*tk;
	t_token	*next_token;

	tk = (t_token *)(*token_lst)->content;
	new_node->redirections = ft_add_to_array(new_node->redirections,
			tk->token_value);
	*token_lst = (*token_lst)->next;
	if (*token_lst)
	{
		next_token = (t_token *)(*token_lst)->content;
		new_node->filename = ft_add_to_array(new_node->filename,
				next_token->token_value);
		*token_lst = (*token_lst)->next;
	}
}

t_node	*parse_tokens(t_list **token_lst)
{
	t_node	*new_node;
	bool	prev_was_redirect;
	t_token	*tk;

	new_node = create_new_node();
	if (!new_node)
		return (NULL);
	prev_was_redirect = false;
	while (*token_lst && ((t_token *)(*token_lst)->content)->tp != PIPE)
	{
		tk = (t_token *)(*token_lst)->content;
		if (tk->tp == WORD || tk->tp == DQT || tk->tp == SQT)
			process_word_token(new_node, token_lst, &prev_was_redirect);
		else if (tk->tp == RI || tk->tp == RO || tk->tp == HRD || tk->tp == APD)
		{
			process_redirection_token(new_node, token_lst);
			prev_was_redirect = true;
		}
		else
		{
			*token_lst = (*token_lst)->next;
			prev_was_redirect = false;
		}
	}
	return (new_node);
}

void	build_parsing_nodes(t_shell *shell)
{
	t_list	*token_lst;
	t_node	*head_node;
	t_node	*current_node;
	t_node	*new_node;

	token_lst = shell->list;
	head_node = NULL;
	current_node = NULL;
	while (token_lst)
	{
		new_node = parse_tokens(&token_lst);
		if (!head_node)
			head_node = new_node;
		else
			current_node->next = new_node;
		current_node = new_node;
		if (token_lst && ((t_token *)token_lst->content)->tp == PIPE)
			token_lst = token_lst->next;
	}
	shell->node = head_node;
}
