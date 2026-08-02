/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_recursive_power.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalbano <dalbano@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 02:24:27 by dalbano           #+#    #+#             */
/*   Updated: 2025/03/26 14:39:09 by dalbano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_power(int nb, int power)
{
	if (power == 0)
		return (1);
	if ((power == 0 && nb == 0) || power < 0)
		return (0);
	if (power > 1)
		nb = nb * ft_power(nb, power -1);
	return (nb);
}

// #include <stdio.h>

// int	main(void)
// {
// 	int	nb = 2;
// 	int power = 5;
// 	printf("%d ^ %d = %d\n", nb, power, ft_recursive_power(nb, power));
// 	return (0);
// }
