/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalbano <dalbano@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 14:43:35 by dalbano           #+#    #+#             */
/*   Updated: 2025/09/08 14:43:37 by dalbano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	update_env_vars(t_shell *shell, char *cwd)
{
	char	buf[PATH_MAX];

	if (cwd && set_env_var(shell, "OLDPWD", cwd) == false)
		return (print_error("cd: failed to set OLDPWD", shell), 1);
	if (getcwd(buf, PATH_MAX) && set_env_var(shell, "PWD", buf) == false)
		return (print_error("cd: failed to set PWD", shell), 1);
	return (0);
}

static char	*get_target_directory(t_shell *shell, char **args, int *error_code)
{
	char	*target_dir;

	if (ft_arrlen(args) > 1)
		return (*error_code = 2, NULL);
	if (ft_arrlen(args) == 0)
	{
		target_dir = env_get(shell->env, "HOME");
		if (!target_dir)
			return (*error_code = 1, NULL);
	}
	else if (ft_strcmp(args[0], "-") == 0)
	{
		target_dir = env_get(shell->env, "OLDPWD");
		if (!target_dir)
			return (*error_code = 1, NULL);
	}
	else
		target_dir = args[0];
	*error_code = 0;
	return (target_dir);
}

static int	handle_target_error(int error_code, char **args, t_shell *shell)
{
	if (error_code == 2)
		return (print_error("cd: too many arguments", shell), 2);
	if (ft_arrlen(args) == 0)
		return (print_error("cd: HOME not set", shell), 1);
	return (print_error("cd: OLDPWD not set", shell), 1);
}

int	exec_cd(t_shell *shell, char **args)
{
	char	*target_dir;
	char	buf[PATH_MAX];
	int		error_code;
	bool	should_free;

	target_dir = get_target_directory(shell, args, &error_code);
	should_free = (ft_arrlen(args) == 0 || ft_strcmp(args[0], "-") == 0);
	if (!target_dir)
		return (handle_target_error(error_code, args, shell));
	if (chdir(target_dir) == -1)
	{
		if (should_free)
			free(target_dir);
		return (print_error("cd: No such file or directory", shell), 1);
	}
	error_code = update_env_vars(shell, getcwd(buf, PATH_MAX));
	if (should_free)
		free(target_dir);
	return (error_code);
}
