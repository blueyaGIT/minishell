/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalbano <dalbano@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 16:29:12 by dalbano           #+#    #+#             */
/*   Updated: 2025/03/22 16:29:28 by dalbano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*gc_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	char	*new;

	if (start > ft_strlen(s))
	{
		len = 0;
		start = 0;
	}
	while ((*s != '\0') && (start-- > 0))
		s++;
	if (ft_strlen(s) < len)
		len = ft_strlen(s);
	substr = gc_malloc(len + 1);
	if (substr == NULL)
		return (NULL);
	new = substr;
	while ((*s != '\0') && (len > 0))
	{
		*new++ = *s++;
		len--;
	}
	*new = '\0';
	return (substr);
}
