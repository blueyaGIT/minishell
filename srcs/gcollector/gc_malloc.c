/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalbano <dalbano@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:32:03 by dalbano           #+#    #+#             */
/*   Updated: 2025/03/12 16:33:36 by dalbano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief works like `malloc()` but also adds the address to the gc list
 * @param size size of memory to allocate.
 * @return pointer to allocated memory.
 */
void	*gc_malloc(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (ptr == NULL)
	{
		print_error(strerror(errno), 0, 0);
		destroy_shell(ft_get_shell(), 1);
		exit(1);
	}
	gc_add(ptr);
	return (ptr);
}
