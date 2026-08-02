/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arr_cpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalbano <dalbano@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 17:18:48 by dalbano           #+#    #+#             */
/*   Updated: 2025/03/26 14:39:09 by dalbano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Creates a deep copy of a string array.
 * @param arr The string array to copy.
 * @return The copied string array on success, NULL on error.
 */
char **ft_arr_cpy(char **arr)
{
    int i = 0;
    while (arr[i])
        i++;

    char **arr_copy = malloc((i + 1) * sizeof(char *));
    if (!arr_copy)
        return (NULL);
    
    i = 0;
    while (arr[i])
    {
        arr_copy[i] = ft_strdup(arr[i]);
        if (!arr_copy[i])
        {
            while (i > 0)
                free(arr_copy[--i]);
            free(arr_copy);
            return (NULL);
        }
        i++;
    }
    arr_copy[i] = NULL;
    return (arr_copy);
}
