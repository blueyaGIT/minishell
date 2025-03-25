/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalbano <dalbano@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 17:32:03 by dalbano           #+#    #+#             */
/*   Updated: 2025/03/25 15:33:21 by dalbano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	dir_init(t_shell *shell)
{
	char	*dir;
	char	*value;
	char	temp[PATH_MAX];

	dir = getcwd(temp, PATH_MAX);
	shell->cur_dir = ft_strdup(dir);
	if (env_idx(shell->env, "OLDPWD") != -1)
	{
		value = env_get(shell->env, "OLDPWD");
		if (!value)
		{
			printf(RED"ERROR: FAILED ENV_GET OLDPWD"RESET);
			exit(EXIT_FAILURE);
		}
		shell->old_dir = ft_strdup(value);
		free(value);
	}
	else
		shell->old_dir = ft_strdup(dir);
	if (!shell->old_dir || !shell->cur_dir)
	{
		printf(RED"ERROR: DIR_INIT FAILED"RESET);
		exit(EXIT_FAILURE);
	}
}

bool	shell_init(t_shell *shell, char **envp)
{
	env_init(shell, envp);
	dir_init(shell);
	shell->heredoc_file = ft_strjoin(shell->cur_dir, HEREDOC_FILE);
	shell->heredoc_index = -1;
	shell->has_error = false;
	shell->last_exitcode = 0;
	return (success);
}
