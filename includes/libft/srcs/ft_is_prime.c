/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_prime.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalbano <dalbano@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 03:22:25 by dalbano           #+#    #+#             */
/*   Updated: 2025/03/26 14:39:09 by dalbano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_is_prime(int nb)
{
	long	temp;

	if (nb == 2)
		return (1);
	if (nb <= 1 || nb % 2 == 0)
		return (0);
	temp = 3;
	while (nb >= temp * temp)
	{
		if (nb % temp == 0)
			return (0);
		temp += 2;
	}
	return (1);
}

// #include <stdio.h>
// #include <limits.h>
// int	main(void)
// {
// 	int nb = 35;
// 	printf("Is %d a prime number?\n%d",nb, ft_is_prime(nb));
// 	return (0);
// }
