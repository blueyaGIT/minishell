/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_arr_cpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalbano <dalbano@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 17:21:28 by dalbano           #+#    #+#             */
/*   Updated: 2025/03/23 12:25:48 by dalbano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**gc_arr_cpy(char **arr)
{
	int		i;
	char	**temp;

	i = 0;
	while (arr[i])
		i++;
	temp = gc_malloc((i + 1) * sizeof(char *));
	if (!temp)
		return (NULL);
	i = 0;
	while (arr[i])
	{
		temp[i] = gc_safe(ft_strdup(arr[i]));
		if (!temp[i])
		{
			gc_free_arr(temp);
			return (NULL);
		}
		i++;
	}
	temp[i] = NULL;
	return (temp);
}
