/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_range.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalbano <dalbano@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 14:33:16 by dalbano           #+#    #+#             */
/*   Updated: 2025/03/26 14:39:09 by dalbano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	*ft_range(int min, int max)
{
	int	*array;
	int	temp;
	int	diff;
	int	temp_min;

	temp = 0;
	temp_min = min - 1;
	diff = 0;
	if (min >= max)
		return (NULL);
	while (max > ++temp_min)
		diff++;
	array = (int *)malloc(diff * sizeof(int));
	if (array == NULL)
		return (0);
	temp_min = min - 1;
	while (max > ++temp_min)
	{
		array[temp] = min;
		min++;
		temp++;
	}
	return (array);
}

// #include <stdio.h>

// void output(int *array, int size)
// {
// 	int i = -1;
// 	while (++i < size)
// 		printf("%d ,", array[i]);
// 	printf("\n");
// }

// int main(void)
// {
// 	int *str;
// 	int *str1;
// 	int *str2;
// 	int *str3;

// 	str = ft_range(-3, 3);
// 	str1 = ft_range(0, 32);
// 	str2 = ft_range(8, 0);
// 	str3 = ft_range(10, 10);
// 	output(str, 6);
// 	output(str1, 32);
// 	printf("%p\n", (void*)str2);
// 	printf("%p\n", (void*)str3);
// 	free(str);
// 	free(str1);
// 	free(str2);
// 	free(str3);
// 	return (0);
// }
