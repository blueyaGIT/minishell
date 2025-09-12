/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalbano <dalbano@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 14:44:34 by dalbano           #+#    #+#             */
/*   Updated: 2025/09/12 12:15:14 by dalbano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Helper function that concatenates three strings.
Assumes ft_strjoin exists.
*/
char	*ft_strjoin_three(const char *s1, const char *s2, const char *s3)
{
	char	*tmp;
	char	*result;

	tmp = ft_strjoin(s1, s2);
	result = ft_strjoin(tmp, s3);
	free(tmp);
	return (result);
}

int	is_valid_varname_export(const char *s)
{
	int	i;

	i = 1;
	if (!s || !(*s) || (!ft_isalpha(*s) && *s != '_'))
		return (0);
	while (s[i] && s[i] != '=')
	{
		if (!ft_isalnum(s[i]) && s[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	update_existing_env(t_shell *shell, char *key, char *value)
{
	int	i;
	int	key_len;

	key_len = ft_strlen(key);
	i = 0;
	while (shell->env[i])
	{
		if (ft_strncmp(shell->env[i], key, key_len) == 0)
		{
			free(shell->env[i]);
			if (value)
				shell->env[i] = ft_strjoin_three(key, "=", value);
			else
				shell->env[i] = ft_strdup(key);
			return (1);
		}
		i++;
	}
	return (0);
}

int	add_new_env(t_shell *shell, char *key, char *value)
{
	int		i;
	char	**new_env;

	i = 0;
	while (shell->env[i])
		i++;
	new_env = malloc(sizeof(char *) * (i + 2));
	if (!new_env)
		return (-1);
	i = -1;
	while (shell->env[++i])
		new_env[i] = shell->env[i];
	if (value)
		new_env[i] = ft_strjoin_three(key, "=", value);
	else
		new_env[i] = ft_strdup(key);
	new_env[i + 1] = NULL;
	free(shell->env);
	shell->env = new_env;
	return (0);
}

int	set_or_update_env(t_shell *shell, char *key, char *value)
{
	if (update_existing_env(shell, key, value))
		return (0);
	return (add_new_env(shell, key, value));
}
