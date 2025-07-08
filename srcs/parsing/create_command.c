/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkloters <lkloters@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 13:05:06 by lkloters          #+#    #+#             */
/*   Updated: 2025/07/08 13:14:53 by lkloters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command *new_command(t_token_type type, char *value)
{
	t_command *new;
	
	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	init_command(new);
	// new->value = value;
	// new->type = type; still to do
	return (new);
}

t_command	*command_last(t_command *command)
{
	if (!command)
		return (NULL);
	while (command->next)
		command = command->next;
	return (command);
}
void	token_add_back(t_command **command, t_command *new)
{
	t_command *temp;
	if (!command || !new)
		return ;
	if (!*command)
		*command = new;
	temp = command_last(*command);
	temp->next = new;
	new->prev = temp;
}