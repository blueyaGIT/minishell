/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_env_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalbano <dalbano@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 14:43:51 by dalbano           #+#    #+#             */
/*   Updated: 2025/09/08 14:43:57 by dalbano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_env(char **env)
{
	int	i;

	i = 0;
	while (env && env[i])
		i++;
	return (i);
}

static void	sort_env(char **env)
{
	int		len;
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	len = count_env(env);
	while (i < len - 1)
	{
		j = 0;
		while (j < len - 1 - i)
		{
			if (ft_strcmp(env[j], env[j + 1]) > 0)
			{
				tmp = env[j];
				env[j] = env[j + 1];
				env[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}

int	show_env_sorted(t_shell *shell)
{
	int	i;

	if (!shell->env)
		return (1);
	sort_env(shell->env);
	i = 0;
	while (shell->env[i])
	{
		ft_printf("declare -x ");
		ft_putendl_fd(shell->env[i], STDOUT_FILENO);
		i++;
	}
	return (0);
}
