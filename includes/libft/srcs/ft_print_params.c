/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_params.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalbano <dalbano@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 17:23:35 by dalbano           #+#    #+#             */
/*   Updated: 2025/03/26 14:39:09 by dalbano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_print_params(int argc, char **argv)
{
	int	temp;
	int	temp2;

	temp = 1;
	while (argc > temp)
	{
		temp2 = 0;
		while (argv[temp][temp2])
		{
			write(1, &argv[temp][temp2], 1);
			temp2++;
		}
		temp++;
		write(1, &"\n", 1);
	}
}
