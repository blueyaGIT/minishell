/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sqrt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalbano <dalbano@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 16:09:29 by dalbano           #+#    #+#             */
/*   Updated: 2025/03/26 14:39:09 by dalbano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_sqrt(int nb)
{
	long	half;
	long	previous;
	int		temp;

	half = nb / 2;
	temp = 0;
	previous = 0;
	if (nb <= 0)
		return (0);
	if (half <= 0)
		half = 1;
	previous = half;
	while (temp < nb)
	{
		if (half * half == nb)
			return (half);
		half = (half + nb / half) / 2;
		if (half == previous)
			return (0);
		previous = half;
		temp++;
	}
	return (half);
}
// #include <stdio.h>
// #include <limits.h>
// int	main(void)
// {
// 	int	nb = 4900;
// 	printf("Sqrt of %d = %d\n", nb, ft_sqrt(nb));
// 	return (0);
// }
