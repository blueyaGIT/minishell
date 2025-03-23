/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalbano <dalbano@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 15:35:55 by dalbano           #+#    #+#             */
/*   Updated: 2025/03/20 16:42:03 by dalbano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_nodefree_ms(t_gcmem *lst)
{
	free(lst->address);
	free(lst);
}

/**
 * @brief works like `free()` but also removes target-address from gcollector-list
 * @param address target-address to free.
 */
void	gc_free(void *address)
{
	t_gcmem	**head;
	t_gcmem	*temp;
	t_gcmem	*prev;

	head = get_head();
	temp = *head;
	prev = NULL;
	while (temp != NULL)
	{
		if (temp->address == address)
		{
			if (prev == NULL)
				*head = temp->next;
			else
				prev->next = temp->next;
			ft_nodefree_ms(temp);
			return ;
		}
		prev = temp;
		temp = temp->next;
	}
}
static void	ft_lstfree_ms(t_gcmem *lst)
{
	t_gcmem	*tmp;

	while (lst)
	{
		tmp = lst->next;
		free(lst->address);
		free(lst);
		lst = tmp;
	}
}

/**
 * @brief Frees gcollector list
 */
void	gc_freeall(void)
{
	t_gcmem	**head;
	t_gcmem	*current;

	head = get_head();
	current = *head;
	ft_lstfree_ms(current);
	set_newhead(NULL);
}
