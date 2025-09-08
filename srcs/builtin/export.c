#include "minishell.h"

static void	parse_key_value(char *arg, char **key, char **value)
{
	char	*equal_sign;

	equal_sign = ft_strchr(arg, '=');
	if (equal_sign)
	{
		*key = ft_substr(arg, 0, equal_sign - arg);
		*value = ft_strdup(equal_sign + 1);
	}
	else
	{
		*key = ft_strdup(arg);
		*value = NULL;
	}
}

static int	handle_export_arg(t_shell *shell, char *arg, int *exit_code)
{
	char	*key;
	char	*value;

	parse_key_value(arg, &key, &value);
	if (!is_valid_varname_export(key))
	{
		ft_printf("export: `%s`: not a valid identifier\n", arg);
		return (free(key), free(value), *exit_code = 1, 0);
	}
	if (set_or_update_env(shell, key, value) == -1)
	{
		ft_printf("export: failed to set environment variable\n");
		*exit_code = 1;
	}
	free(key);
	free(value);
	return (0);
}

int	exec_export(t_shell *shell, char **args)
{
	int	i;
	int	exit_code;

	if (ft_arrlen(args) == 0)
		return (show_env_sorted(shell));
	exit_code = 0;
	i = 0;
	while (args[i])
	{
		handle_export_arg(shell, args[i], &exit_code);
		i++;
	}
	return (exit_code);
}
