

#include "minishell.h"

static int	get_ecode(char *param, bool *temp)
{
	unsigned long long	i;

	i = 0;
	if (!param)
		return (g_ecode);
	while (ft_isspace(param[i]))
		i++;
	if (param[i] == '\0')
		return (*temp = true, 0);
	if (param[i] == '+' || param[i] == '-')
		i++;
	if (!ft_isdigit(param[i]))
		return (*temp = true, 0);
	while (param[i] != '\0')
		if (!ft_isdigit(param[i]) && !ft_isspace(param[i]))
			return (*temp = true, 0);
	else
		i++;
	i = ft_atoll(&param[i], temp);
	return ((int)(i % 256));
}

static bool	check_commands(t_shell *shell)
{
	t_command	*temp;

	temp = shell->cmd_list;
	if (!temp)
		return (true);
	if (temp->next != NULL || temp->prev != NULL)
		return (false);
	return (true);
}

int	exec_exit(t_shell *shell, char **args)
{
	int		ecode;
	bool	temp;

	temp = false;
	if (check_commands(shell))
		ft_putendl_fd("exit", 2);
	if (!args || !args[1])
		ecode = g_ecode;
	else
	{
		ecode = get_ecode(args[1], &temp);
		if (temp)
			return (ft_putendl_fd("numeric argument required", 2),
				kill_shell(shell, 255), 255);
		else if (args[2])
			return (ft_putendl_fd("too many arguments", 2), 1);
	}
	return (kill_shell(shell, ecode), ecode);
}
