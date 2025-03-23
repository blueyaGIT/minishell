/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalbano <dalbano@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 16:26:45 by dalbano           #+#    #+#             */
/*   Updated: 2025/03/22 16:27:10 by dalbano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*gc_strdup(char *src)
{
	int		count;
	char	*array;
	int		temp;

	count = 0;
	temp = 0;
	while (src[count] != '\0')
		count++;
	array = (char *)gc_malloc((count + 1) * sizeof(char));
	if (array == NULL)
		return (0);
	while (temp <= count)
	{
		array[temp] = src[temp];
		temp++;
	}
	return (array);
}
