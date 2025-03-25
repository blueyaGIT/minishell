/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalbano <dalbano@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 17:40:10 by dalbano           #+#    #+#             */
/*   Updated: 2025/03/25 17:12:28 by dalbano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*find_shlvl_value(char **env)
{
	int	i;

	i = -1;
	i = env_idx(env, "SHLVL");
	if (i != -1)
		return(env[i] + ft_strlen("SHLVL="));
	return (NULL);
}

/**
 * @brief handles SHLVL value
 * if shlvl value doesn't exist, we create it with value (1)
 * if shlvl value exists, we add to it in steps of value (1)
 * @param shell t_shell struct
 */
void	check_shlvl(t_shell *shell)
{
	char	*shlvl;
	char	*value;
	int		lvl;

	shlvl = find_shlvl_value(shell->env);
	if (!shlvl)
	{
		value = ft_itoa(1);
		if (!value)
			return ;
		set_env_var(shell, "SHLVL", value);
		free(value);
		return ;
	}
	lvl = ft_atoi(shlvl) + 1;
	if (lvl < 0 || lvl > 999)
		lvl = 0;
	value = ft_itoa(lvl);
	if (!value)
		return ;
	set_env_var(shell, "SHLVL", value);
	free(value);
}

/**
 * @brief Manually sets shell->env with all necessary data
 * sets PWD, SHLVL and adds another NULL-string
 * @param shell our t_shell struct
 */
static void configure_env(t_shell *shell)
{
	char	temp[PATH_MAX];
	
	shell->env = malloc(sizeof(char *) * 3);
	if (!shell->env)
	{
		printf(RED"Error: FAILED TO ALLOCATE SHELL->ENV"RESET);
		exit(EXIT_FAILURE);
	}
	shell->env[0] = ft_strjoin("PWD=", getcwd(temp, PATH_MAX));
	if (!shell->env[0])
	{
		printf(RED"Error: FAILED TO SET PWD IN SHELL->ENV[0]"RESET);
		exit(EXIT_FAILURE);
	}
	shell->env[1] = ft_strdup("SHLVL=1");
	if (!shell->env[1])
	{
		printf(RED"Error: FAILED TO SET SHLVL IN SHELL->ENV[1]"RESET);
		exit(EXIT_FAILURE);
	}
	shell->env[2] = NULL;
}

/**
 * Sets pwd to init env if not set already
 * handles SHLVL
 * @param shell t_shell struct
 * @param env env-variable
 */
void	env_init(t_shell *shell, char **envp)
{
	if (!envp || envp[0] == NULL)
	{
		configure_env(shell);
		return ;
	}
	shell->env = copy_env(envp);
	check_shlvl(shell);
}
