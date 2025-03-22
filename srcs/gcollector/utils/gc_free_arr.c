/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_free_arr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalbano <dalbano@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 17:28:25 by dalbano           #+#    #+#             */
/*   Updated: 2025/03/22 17:32:58 by dalbano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	gc_free_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		gc_free(arr[i]);
		i++;
	}
	gc_free(arr);
}
