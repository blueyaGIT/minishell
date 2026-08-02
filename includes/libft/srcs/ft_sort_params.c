/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_params.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalbano <dalbano@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 04:02:05 by dalbano           #+#    #+#             */
/*   Updated: 2025/03/26 14:39:09 by dalbano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_sort_params_output(char *str)
{
	while (*str)
	{
		write(1, str, 1);
		str++;
	}
}

void	ft_sort_params_sort(int argc, char **argv)
{
	int		swap;
	char	*placeholder;
	int		temp;

	while (1)
	{
		swap = 0;
		temp = 1;
		while (temp < argc - 1)
		{
			if (ft_sort_params_compareascii(argv[temp], argv[temp + 1]) > 0)
			{
				placeholder = argv[temp];
				argv[temp] = argv[temp + 1];
				argv[temp + 1] = placeholder;
				swap = 1;
			}
			temp++;
		}
		if (swap == '\0')
			return ;
	}
}

int	ft_sort_params_compareascii(char *str1, char *str2)
{
	while (*str1 && *str2 && *str1 == *str2)
	{
		str1++;
		str2++;
	}
	return (*str1 - *str2);
}

void	ft_sort_params(int argc, char **argv)
{
	int	temp;

	ft_sort_params_sort(argc, argv);
	temp = 1;
	while (temp < argc)
	{
		ft_sort_params_output(argv[temp]);
		write(1, &"\n", 1);
		temp++;
	}
}
