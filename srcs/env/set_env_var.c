/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalbano <dalbano@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 13:33:54 by dalbano           #+#    #+#             */
/*   Updated: 2025/03/23 14:27:26 by dalbano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**refresh_env(t_shell *shell, int size)
{
	int		i;
	char	**temp;

	temp = gc_calloc(sizeof(char **), (size + 1));
	if (!temp)
		return (NULL);
	i = 0;
	while (shell->env[i] && i < size)
	{
		temp[i] = gc_strdup(shell->env[i]);
		ft_free_ptr(shell->env[i]);
		i++;
	}
	gc_free(shell->env);
	return (temp);
}

bool	set_env_var(t_shell *shell, char *key, char *value)
{
	int		idx;
	char	*temp;

	idx = env_idx(shell->env, key);
	if (value == NULL)
		value = "";
	temp = gc_strjoin("=", value);
	if (!temp)
		return (fail);
	if (idx >= 0 && shell->env[idx])
	{
		ft_free_ptr(shell->env[idx]);
		shell->env[idx] = gc_strjoin(key, temp);
	}
	else
	{
		idx = ft_arrlen(shell->env);
		shell->env = refresh_env(shell, idx + 1);
		if (!shell->env)
			return (fail);
		shell->env[idx] = gc_strjoin(key, temp);
	}
	ft_free_ptr(temp);
	return (success);
}