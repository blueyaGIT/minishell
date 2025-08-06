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

static char	*get_target_directory(char **args, int *error_code)
{
	char	*target_dir;

	if (ft_arrlen(args) > 1)
		return (*error_code = 2, NULL);
	if (ft_arrlen(args) == 0)
	{
		target_dir = getenv("HOME");
		if (!target_dir)
			return (*error_code = 1, NULL);
	}
	else if (ft_strcmp(args[0], "-") == 0)
	{
		target_dir = getenv("OLDPWD");
		if (!target_dir)
			return (*error_code = 1, NULL);
	}
	else
		target_dir = args[0];
	*error_code = 0;
	return (target_dir);
}

int	exec_cd(t_shell *shell, char **args)
{
	char	*cwd;
	char	*target_dir;
	char	buf[PATH_MAX];
	int		error_code;

	target_dir = get_target_directory(args, &error_code);
	if (!target_dir)
	{
		if (error_code == 2)
			return (print_error("cd: too many arguments", shell), 2);
		else if (error_code == 1)
		{
			if (ft_arrlen(args) == 0)
				return (print_error("cd: HOME not set", shell), 1);
			else
				return (print_error("cd: OLDPWD not set", shell), 1);
		}
	}
	cwd = getcwd(buf, PATH_MAX);
	if (chdir(target_dir) == -1)
		return (print_error("cd", shell), 1);
	return (update_env_vars(shell, cwd));
}
