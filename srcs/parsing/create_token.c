/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkloters <lkloters@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 17:25:12 by lkloters          #+#    #+#             */
/*   Updated: 2025/07/01 17:32:57 by lkloters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token *new_token(t_token_type type, char *value)
{
	t_token *new;
	
	new = malloc(sizeof(t_token));
	if (!new)
		free_token(new); // still to do
	new->value = value;
	new->type = type;
	new->next = NULL;
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
	if (!token)
		return ;
	if (!*token)
		*token = new;
	else
		(token_last(*token))->next = new;
}