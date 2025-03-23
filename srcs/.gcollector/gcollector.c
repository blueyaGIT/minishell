/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gcollector.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalbano <dalbano@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 15:02:16 by dalbano           #+#    #+#             */
/*   Updated: 2025/03/20 16:55:11 by dalbano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Holds static reference to gcollector-list.
 * @return 1st node of gcollector-list.
 */
t_gcmem	**get_head(void)
{
	static t_gcmem	*gc_head;
	return (&gc_head);
}

/**
 * @brief works like `malloc()` but also adds target-address to gcollector-list
 * @param size size of memory to allocate.
 * @return pointer to allocated memory.
 */
void	*gc_malloc(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (ptr == NULL)
	{
		// print_error(strerror(errno), 0, 0);
		kill_shell(get_shell(), 1);
		exit(1);
	}
	gc_add(ptr);
	return (ptr);
}

/**
 * @brief changes static reference stored in `get_head()` to new location/node
 * @param new_head new head of gcollector-list
 */
void	set_newhead(t_gcmem *new_head)
{
	t_gcmem	**head;

	head = get_head();
	*head = new_head;
}
