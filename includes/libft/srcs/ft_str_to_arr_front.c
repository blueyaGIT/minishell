/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_to_arr_front.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalbano <dalbano@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 16:06:03 by dalbano           #+#    #+#             */
/*   Updated: 2025/04/09 16:33:01 by dalbano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * prepend_str_to_array - Adds a new string to the beginning of a
 *                        NULL-terminated array of strings.
 *
 * This function reallocates the given string array to prepend a duplicate
 * of the provided string and ensures the array remains NULL-terminated.
 *
 * @param array: The original array of strings (can be NULL).
 * @param str: The string to add. A duplicate of this string will be stored.
 *
 * @return A pointer to the new array with the added string at the front, or NULL on allocation failure.
 */
char **ft_str_to_array_front(char **array, char *str)
{
    int		len;
	char	**new_array;
	int		i;

	len = 0;
	i = 1;
	while (array && array[len])
		len++;
	new_array = malloc(sizeof(char *) * (len + 2));
	if (!new_array)
		return (NULL);
	new_array[0] = ft_strdup(str);
	while (i <= len)
	{
		new_array[i] = ft_strdup(array[i - 1]);
		i++;
	}
	new_array[i] = NULL;
	ft_free_arr(array);
	return (new_array);
}
