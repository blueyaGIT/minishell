

#include "minishell.h"

char	**refresh_env(t_shell *shell, int size)
{
	int		i;
	char	**temp;

	temp = ft_calloc(sizeof(char **), (size + 1));
	if (!temp)
		return (NULL);
	i = 0;
	while (shell->env[i] && i < size)
	{
		temp[i] = ft_strdup(shell->env[i]);
		ft_free_ptr(shell->env[i]);
		i++;
	}
	free(shell->env);
	shell->env = NULL;
	return (temp);
}

bool	set_env_var(t_shell *shell, char *key, char *value)
{
	int		idx;
	char	*temp;

	idx = env_idx(shell->env, key);
	if (value == NULL)
		value = "";
	temp = ft_strjoin("=", value);
	if (!temp)
		return (FAIL);
	if (idx >= 0 && shell->env[idx])
	{
		ft_free_ptr(shell->env[idx]);
		shell->env[idx] = ft_strjoin(key, temp);
	}
	else
	{
		idx = ft_arrlen(shell->env);
		shell->env = refresh_env(shell, idx + 1);
		if (!shell->env)
			return (ft_free_ptr(temp), FAIL);
		shell->env[idx] = ft_strjoin(key, temp);
	}
	ft_free_ptr(temp);
	return (SUCCESS);
}
