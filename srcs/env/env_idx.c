/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_idx.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalbano <dalbano@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 14:45:56 by dalbano           #+#    #+#             */
/*   Updated: 2025/09/08 14:45:57 by dalbano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Gets the idx of an entry in the environment.
 * @param env env to search in.
 * @param key key to search for.
 * @return idx of entry if SUCCESS; -1 on error or not found.
 */
int	env_idx(char **env, char *key)
{
	int	temp;
	int	len;

	temp = 0;
	len = ft_strlen(key);
	while (env[temp])
	{
		if (ft_strncmp(env[temp], key, len) == 0)
		{
			if (env[temp][len] == '=' || env[temp][len] == '\0')
				return (temp);
		}
		temp++;
	}
	return (-1);
}
