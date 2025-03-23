/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalbano <dalbano@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 16:18:37 by dalbano           #+#    #+#             */
/*   Updated: 2025/03/22 16:18:52 by dalbano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

static int	get_num_length(int n)
{
	int	len;

	len = (n <= 0);
	while (n != 0)
	{
		len++;
		n /= 10;
	}
	return (len);
}

char	*gc_itoa(int n)
{
	int		len;
	char	*str;
	long	num;

	len = get_num_length(n);
	str = (char *)gc_malloc((len + 1) * sizeof(char));
	num = n;
	if (!str)
		return (NULL);
	str[len] = '\0';
	if (num < 0)
	{
		str[0] = '-';
		num *= -1;
	}
	while (len-- > (n < 0))
	{
		str[len] = '0' + (num % 10);
		num /= 10;
	}
	return (str);
}
