/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_get.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalbano <dalbano@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:01:55 by dalbano           #+#    #+#             */
/*   Updated: 2025/03/22 16:35:09 by dalbano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Get the value of an environment variable (envvar).
 * @param env environment variables.
 * @param key key to envvars.
 * @return value of envvars or NULL.
 */
char	*env_get(char **env, char *key)
{
	int		idx;
	char	*entry;
	char	*value;
	char	*temp;

	idx = env_idx(env, key);
	if (idx == -1)
		return (NULL);
	entry = env[idx];
	temp = ft_strchr(entry, '=');
	if (temp == NULL)
		return (NULL);
	if (temp[1] == '\0')
		value = (char *)gc_safe(ft_strdup(""));
	else
		value = (char *)gc_safe(ft_strdup(temp + 1));
	if (value == NULL)
		return (NULL);
	return (value);
}
