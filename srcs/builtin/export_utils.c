/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkloters <lkloters@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 14:44:34 by dalbano           #+#    #+#             */
/*   Updated: 2026/08/01 19:59:07 by lkloters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin_three(const char *s1, const char *s2, const char *s3)
{
	char	*tmp;
	char	*result;

	tmp = ft_strjoin(s1, s2);
	if (!tmp)
		return (NULL);
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
	int		i;
	int		key_len;
	char	*new_var;

	key_len = ft_strlen(key);
	i = 0;
	while (shell->env[i])
	{
		if (ft_strncmp(shell->env[i], key, key_len) == 0)
		{
			if (value)
				new_var = ft_strjoin_three(key, "=", value);
			else
				new_var = ft_strdup(key);
			if (!new_var)
				return (0);
			free(shell->env[i]);
			shell->env[i] = new_var;
			return (1);
		}
		i++;
	}
	return (0);
}
