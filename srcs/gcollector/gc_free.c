/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalbano <dalbano@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 16:03:07 by flfische          #+#    #+#             */
/*   Updated: 2025/03/19 13:31:46 by dalbano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief works like `free()` but also removes the address from the gc list
 * @param address The address to free.
 */
void	gc_free(void *address)
{
	t_memblock	**head;
	t_memblock	*prev;
	t_memblock	*next;

	head = ft_gc_get();
	prev = NULL;
	next = *head;
	while (next != NULL)
	{
		if (next->address == address)
		{
			if (prev == NULL)
				*head = next->next;
			else
				prev->next = next->next;
			free(next->address);
			free(next);
			return ;
		}
		prev = next;
		next = next->next;
	}
}
