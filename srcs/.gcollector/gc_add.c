/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_add.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalbano <dalbano@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 15:36:02 by dalbano           #+#    #+#             */
/*   Updated: 2025/03/20 16:40:07 by dalbano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Adds an address to the garbage collector list.
 * @param address The address to add.
 */
void	gc_add(void *address)
{
	t_gcmem	**head;
	t_gcmem	*new;

	head = get_head();
	new = malloc(sizeof(t_gcmem));
	if (new == NULL)
	{
		// print_error(strerror(errno), 0, 0);
		return (kill_shell(get_shell(), 1), (void)0);
	}
	new->address = address;
	new->next = *head;
	*head = new;
}

void	*gc_safe(void *address)
{
	if (address == NULL)
	{
		// print_error(strerror(errno), 0, 0);
		kill_shell(get_shell(), 1);
	}
	gc_add(address);
	return (address);
}
