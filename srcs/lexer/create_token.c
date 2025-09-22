/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkloters <lkloters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 14:46:35 by dalbano           #+#    #+#             */
/*   Updated: 2025/09/22 15:19:20 by lkloters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_token(t_token *token)
{
	if (!token)
		return ;
	token->value = NULL;
	token->type = 0;
	token->is_echo = false;
	token->is_echo_n = false;
	token->is_removed = false;
	token->add_space = false;
	token->next = NULL;
	token->prev = NULL;
}

t_token	*new_token(t_token_type type, char *value)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	init_token(new);
	new->value = value;
	new->type = type;
	return (new);
}

t_token	*token_last(t_token *token)
{
	if (!token)
		return (NULL);
	while (token->next)
		token = token->next;
	return (token);
}

void	token_add_back(t_token **token, t_token *new)
{
	t_token	*temp;

	if (!token || !new)
		return ;
	if (!*token)
	{
		*token = new;
		return ;
	}
	temp = token_last(*token);
	temp->next = new;
	new->prev = temp;
}
