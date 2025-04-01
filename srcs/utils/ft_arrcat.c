/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalbano <dalbano@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 15:57:19 by dalbano           #+#    #+#             */
/*   Updated: 2025/04/01 16:02:52 by dalbano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * add_str_to_array - Adds a new string to a NULL-terminated array of strings.
 *
 * This function reallocates the given string array to append a duplicate of the
 * provided string and ensures the array remains NULL-terminated.
 *
 * @param array: The original array of strings (can be NULL).
 * @param str: The string to add. A duplicate of this string will be stored.
 *
 * @return A pointer to the new array containing the added string, or NULL on allocation failure.
 */
char **add_str_to_array(char **array, char *str)
{
    size_t count = 0;
    char **new_array;

    if (array)
    {
        while (array[count])
            count++;
    }
    new_array = ft_realloc(array, sizeof(char *) * (count + 2));
    if (!new_array)
        return (NULL);
    new_array[count] = ft_strdup(str);
    if (!new_array[count])
        return (NULL);
    new_array[count + 1] = NULL;
    return (new_array);
}
