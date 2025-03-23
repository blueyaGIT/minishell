/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalbano <dalbano@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 16:28:11 by dalbano           #+#    #+#             */
/*   Updated: 2025/03/22 16:28:31 by dalbano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_join_strcpy(char *dest, const char *src)
{
	char	*ptr;

	ptr = dest;
	while (*src != '\0')
	{
		*ptr++ = *src++;
	}
	*ptr = '\0';
	return (dest);
}

static char	*ft_join_strcat(char *dest, const char *src)
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

char	*gc_strjoin(char const *s1, char const *s2)
{
	size_t	len1;
	size_t	len2;
	char	*joined_str;

	if (!s1 || !s2)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	joined_str = (char *)gc_malloc(len1 + len2 + 1);
	if (!joined_str)
		return (NULL);
	ft_join_strcpy(joined_str, s1);
	ft_join_strcat(joined_str, s2);
	return (joined_str);
}
