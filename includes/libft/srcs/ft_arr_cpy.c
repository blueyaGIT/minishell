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

static int	ft_arr_len(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

static char	**copy_arr_strings(char **arr, char **arr_copy, int len)
{
	int	i;

	i = 0;
	while (i < len)
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
	arr_copy[len] = NULL;
	return (arr_copy);
}

char	**ft_arr_cpy(char **arr)
{
	int		len;
	char	**arr_copy;

	len = ft_arr_len(arr);
	arr_copy = malloc((len + 1) * sizeof(char *));
	if (!arr_copy)
		return (NULL);
	return (copy_arr_strings(arr, arr_copy, len));
}
