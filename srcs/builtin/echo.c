#include "minishell.h"

int	exec_echo(t_shell *shell, char **args)
{
	int	i;
	int	status;

	i = 0;
	status = 0;
	while (args[i])
	{

		if (status == -1)
			return (EXIT_FAILURE);
		status = ft_printf(args[i], 1);
		if (status == -1)
			return (EXIT_FAILURE);
		i++;
	}
	if (!shell->cmd_list->is_echo_n)
		status = ft_printf("\n", 1);
	if (status == -1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
