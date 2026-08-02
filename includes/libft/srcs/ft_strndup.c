/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalbano <dalbano@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 11:40:00 by dalbano           #+#    #+#             */
/*   Updated: 2025/03/26 14:39:09 by dalbano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *src, size_t n)
{
	size_t	count;
	char	*array;
	size_t	i;

	count = 0;
	while (src[count] != '\0' && count < n)
		count++;
	array = (char *)malloc((count + 1) * sizeof(char));
	if (array == NULL)
		return (0);
	i = 0;
	while (i < count)
	{
		array[i] = src[i];
		i++;
	}
	array[i] = '\0';
	return (array);
}
