/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalbano <dalbano@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 15:28:10 by dalbano           #+#    #+#             */
/*   Updated: 2025/04/12 16:15:55 by dalbano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_valid_varname(const char *s)
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

static int	set_or_update_env(t_shell *shell, char *key, char *value)
{
	int		i;
    int		key_len;
    char	**new_env;

    key_len = ft_strlen(key);
    i = 0;
	while (shell->env[i])
    {
        if (ft_strncmp(shell->env[i], key, key_len) == 0 && shell->env[i][key_len] == '=')
        {
            free(shell->env[i]);
            if (value)
                shell->env[i] = ft_strjoin_three(key, "=", value);
            else
                shell->env[i] = ft_strdup(key);
            return (0);
        }
        i++;
    }
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

int	exec_export(t_shell *shell, char **args)
{
	int		i;
	int		exit_code;
	char	*equal_sign;
	char	*key;
	char	*value;

	if (ft_arrlen(args) == 0)
		return (exec_env(shell, NULL));
	i = 0;
	while (args[i])
	{
		equal_sign = ft_strchr(args[i], '=');
        if (equal_sign)
        {
            key = ft_substr(args[i], 0, equal_sign - args[i]);
            value = ft_strdup(equal_sign + 1);
        }
        else
        {
            key = ft_strdup(args[i]);
            value = NULL;
        }
        if (!is_valid_varname(key))
        {
            ft_printf("export: `%s`: not a valid identifier\n", args[i]);
            free(key);
            free(value);
			exit_code = 2;
            i++;
            continue;
        }
		if (set_or_update_env(shell, key, value) == -1)
        {
            ft_printf("export: failed to set environment variable\n");
            exit_code = 1;
        }
        free(key);
        free(value);
        i++;
    }
	shell->env = refresh_env(shell, ft_arrlen(shell->env));
    return (exit_code);
}
