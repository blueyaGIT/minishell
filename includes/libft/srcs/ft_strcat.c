/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalbano <dalbano@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 13:36:27 by dalbano           #+#    #+#             */
/*   Updated: 2025/03/26 14:39:09 by dalbano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat(char *dest, char *src)
{
	int	x;

	x = 0;
	while (dest[x] != '\0')
		x++;
	while (*src != '\0')
	{
		dest[x] = *src;
		x++;
		src++;
	}
	dest[x] = '\0';
	return (dest);
}
