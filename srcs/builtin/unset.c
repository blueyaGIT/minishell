#include "minishell.h"

// static int	is_valid_identifier(t_shell *shell, char *str)
// {
// 	int	idx;

// 	idx = env_idx(shell->env, str);
// 	if (idx == -1)
// 		return (0);
// 	return (idx);
// }

static bool	remove_env_var(t_shell *shell, int idx)
{
	int	i;

	if (idx > ft_arrlen(shell->env))
		return (FAIL);
	ft_free_ptr(shell->env[idx]);
	i = idx;
	while (shell->env[i + 1])
	{
		shell->env[i] = ft_strdup(shell->env[i + 1]);
		ft_free_ptr(shell->env[i + 1]);
		i++;
	}
	shell->env = refresh_env(shell, i);
	if (!shell->env)
		return (FAIL);
	return (true);
}

bool	is_valid_varname(char *str)
{
	int	i;

	if (!str || !*str)
		return (false);
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (false);
	i = 1;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (false);
		i++;
	}
	return (true);
}

int	exec_unset(t_shell *shell, char **args)
{
	int	i;
	int	exit_status;
	int	idx;

	exit_status = 0;
	i = 0;
	if (!args[0])
		return (0);
	while (args[i])
	{
		if (!is_valid_varname(args[i]))
		{
			ft_printf("unset: `%s': not a valid identifier\n", args[i]);
			exit_status = 1;
		}
		else
		{
			idx = env_idx(shell->env, args[i]);
			if (idx != -1)
				if (remove_env_var(shell, idx) == false)
					return (ft_printf("unset: failed to remove variable\n"), 1);
		}
		i++;
	}
	return (exit_status);
}
