/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkloters <lkloters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 14:46:00 by dalbano           #+#    #+#             */
/*   Updated: 2025/09/08 14:54:54 by lkloters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**refresh_env(t_shell *shell, int size)
{
	int		i;
	char	**temp;

	temp = ft_calloc(sizeof(char **), (size + 1));
	if (!temp)
		return (NULL);
	i = 0;
	while (shell->env[i] && i < size)
	{
		temp[i] = ft_strdup(shell->env[i]);
		ft_free_ptr(shell->env[i]);
		i++;
	}
	free(shell->env);
	shell->env = NULL;
	return (temp);
}

static bool	update_existing_var(t_shell *shell, int idx, char *key, char *temp)
{
	char	*new_var;

	new_var = ft_strjoin(key, temp);
	if (!new_var)
		return (false);
	ft_free_ptr(shell->env[idx]);
	shell->env[idx] = new_var;
	return (true);
}

static bool	add_new_var(t_shell *shell, char *key, char *temp)
{
	int		idx;
	char	*new_var;

	idx = ft_arrlen(shell->env);
	shell->env = refresh_env(shell, idx + 1);
	if (!shell->env)
		return (false);
	new_var = ft_strjoin(key, temp);
	if (!new_var)
		return (false);
	shell->env[idx] = new_var;
	return (true);
}

bool	set_env_var(t_shell *shell, char *key, char *value)
{
	int		idx;
	char	*temp;
	bool	result;

	idx = env_idx(shell->env, key);
	if (value == NULL)
		value = "";
	temp = ft_strjoin("=", value);
	if (!temp)
		return (false);
	if (idx >= 0 && shell->env[idx])
		result = update_existing_var(shell, idx, key, temp);
	else
		result = add_new_var(shell, key, temp);
	ft_free_ptr(temp);
	return (result);
}
