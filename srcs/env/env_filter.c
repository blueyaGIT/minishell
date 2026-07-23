/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_filter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkloters <lkloters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/23 00:00:00 by lkloters          #+#    #+#             */
/*   Updated: 2026/07/23 00:00:00 by lkloters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_valued(char **env)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (env && env[i])
	{
		if (ft_strchr(env[i], '='))
			count++;
		i++;
	}
	return (count);
}

/**
 * @brief Builds an envp-style array containing only the entries that
 * carry a value (i.e. "KEY=VALUE"). Variables exported without a value
 * (e.g. via `export A`) are skipped, since they are not part of the
 * environment until they are assigned one.
 * The returned strings are shared with shell->env and must not be freed
 * individually; only the array itself should be freed.
 */
char	**build_envp(char **env)
{
	char	**envp;
	int		i;
	int		j;

	envp = ft_calloc(count_valued(env) + 1, sizeof(char *));
	if (!envp)
		return (NULL);
	i = 0;
	j = 0;
	while (env && env[i])
	{
		if (ft_strchr(env[i], '='))
			envp[j++] = env[i];
		i++;
	}
	return (envp);
}
