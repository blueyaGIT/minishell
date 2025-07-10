/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkloters <lkloters@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 17:25:12 by lkloters          #+#    #+#             */
/*   Updated: 2025/07/10 19:44:13 by lkloters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token *new_token(t_token_type type, char *value)
{
	t_token *new;
	
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
	t_token *temp;
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