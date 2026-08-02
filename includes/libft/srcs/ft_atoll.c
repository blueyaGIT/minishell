/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalbano <dalbano@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 14:16:56 by dalbano           #+#    #+#             */
/*   Updated: 2025/03/26 14:47:02 by dalbano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long long	is_overflowing(long long result, char next_digit, int sign)
{
	if (sign == 1 && result > (LLONG_MAX - (next_digit - '0')) / 10)
		return (LLONG_MAX);
	if (sign == -1 && result > (LLONG_MIN + (next_digit - '0')) / -10)
		return (LLONG_MIN);
	return (0);
}


long long	ft_atoll(const char *str, bool *overflow)
{
	int			sign;
	long long	result;

	sign = 1;
	result = 0;
	*overflow = false;
	while (*str == ' ' || (*str >= '\t' && *str <= '\r'))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		if (is_overflowing(result, *str, sign) != 0)
			return (*overflow = true, is_overflowing(result, *str, sign));
		result = result * 10 + (*str - '0');
		str++;
	}
	if (*str != '\0' && !(*str == ' ' || (*str >= '\t' && *str <= '\r')))
		*overflow = true;

	return (sign * result);
}
