/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalbano <dalbano@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 15:59:16 by dalbano           #+#    #+#             */
/*   Updated: 2025/04/09 10:00:27 by dalbano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	helper_func(size_t old_size, size_t new_size, size_t *copy_size)
{
    if (old_size < new_size)
    {
		*copy_size = old_size;
	}
    else
    {
		*copy_size = new_size;
	}
}

/*
 * ft_realloc manually resizes the memory block pointed by ptr to size bytes.
 * It assumes that a header (of type size_t) was stored immediately before ptr
 * that contains the size of the allocated block.
 *
 * If ptr is NULL, behaves like malloc(size).
 * If size is 0, frees ptr and returns NULL.
 */
void    *ft_realloc(void *ptr, size_t size)
{
    void    *new_ptr;
    size_t  old_size;
    size_t  copy_size;

    if (!ptr)
	{
		return (malloc(size));
	}
    if (size == 0)
    {
        free(ptr);
        return (NULL);
    }
    old_size = *((size_t *)ptr - 1);
    new_ptr = malloc(size);
    if (!new_ptr)
	{
		return (NULL);
	}
	helper_func(old_size, size, &copy_size);
    ft_memcpy(new_ptr, ptr, copy_size);
    free(ptr);
    return (new_ptr);
}
