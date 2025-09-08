/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_copy.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalbano <dalbano@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 14:45:53 by dalbano           #+#    #+#             */
/*   Updated: 2025/09/08 14:45:54 by dalbano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**copy_env(char **env)
{
	int		i;
	char	**env_copy;

	i = 0;
	while (env[i])
		i++;
	env_copy = ft_calloc(i + 1, sizeof(char *));
	if (!env_copy)
		return (NULL);
	i = 0;
	while (env[i])
	{
		env_copy[i] = ft_strdup(env[i]);
		if (!env_copy[i])
		{
			while (i > 0)
				ft_free_ptr(env_copy[--i]);
			free(env_copy);
			env_copy = NULL;
			return (NULL);
		}
		i++;
	}
	env_copy[i] = NULL;
	return (env_copy);
}
