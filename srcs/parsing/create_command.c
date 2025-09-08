/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalbano <dalbano@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 14:46:55 by dalbano           #+#    #+#             */
/*   Updated: 2025/09/08 14:46:56 by dalbano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command	*new_command(void)
{
	t_command	*new;

	new = malloc(sizeof(t_command));
	if (!new)
		return (NULL);
	init_command(new);
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

void	command_add_back(t_command **command, t_command *new)
{
	t_command	*temp;

	if (!command || !new)
		return ;
	if (!*command)
	{
		*command = new;
		return ;
	}
	temp = command_last(*command);
	temp->next = new;
	new->prev = temp;
}
