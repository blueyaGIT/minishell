#include "minishell.h"

int	exec_cd(t_shell *shell, char **args)
{
	char	*cwd;
	char	buf[PATH_MAX];

	if (ft_arrlen(args) > 2)
		return (print_error("CD", shell), 2);
	cwd = getcwd(buf, PATH_MAX);
	if (chdir(args[0]) == -1)
		return (print_error("CD", shell), 2);
	if (set_env_var(shell, "OLDPWD", cwd) == false)
		return (print_error("ENV-VAR", shell), 1);
	return (0);
}
