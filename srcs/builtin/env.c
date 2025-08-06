#include "minishell.h"

int	exec_env(t_shell *shell, char **args)
{
	int	i;

	i = 0;
	if (args && args[0])
		return (ft_putendl_fd("env: too many arguments", STDERR_FILENO), 125);
	if (!shell->env)
		return (ft_putendl_fd("env: environment not available", STDERR_FILENO),
			1);
	while (shell->env[i])
		ft_putendl_fd(shell->env[i++], STDOUT_FILENO);
	return (EXIT_SUCCESS);
}
