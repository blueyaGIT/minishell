/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalbano <dalbano@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 16:14:53 by dalbano           #+#    #+#             */
/*   Updated: 2025/03/22 16:15:36 by dalbano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*gc_calloc(size_t count, size_t size)
{
	size_t			total;
	size_t			temp;
	void			*memory;
	unsigned char	*ptr;

	total = count * size;
	memory = gc_malloc(total);
	if (!memory)
		return (NULL);
	ptr = memory;
	temp = -1;
	while (++temp < total)
	{
		ptr[temp] = 0;
	}
	return (memory);
}
