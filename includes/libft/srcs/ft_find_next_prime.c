/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_next_prime.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalbano <dalbano@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 03:30:28 by dalbano           #+#    #+#             */
/*   Updated: 2025/03/26 14:39:09 by dalbano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_prime(int nb)
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

int	ft_find_next_prime(int nb)
{
	int	temp;

	temp = nb;
	if (nb != 2)
		temp++;
	while (is_prime(temp) != 1)
	{
		temp++;
	}
	return (temp);
}

// #include <stdio.h>
// int	main(void)
// {
// 	int nb = 3;
// 	printf("Current prime: %d\n Next prime: %d\n", nb, ft_find_next_prime(nb));
// 	return (0);
// }
