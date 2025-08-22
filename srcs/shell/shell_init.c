#include "minishell.h"

// static void	dir_init(t_shell *shell)
// {
// 	// char	*dir;
// 	char	*value;
// 	// char	temp[PATH_MAX];

// 	// dir = getcwd(temp, PATH_MAX);
// 	// shell->cur_dir = ft_strdup(dir);
// 	if (env_idx(shell->env, "OLDPWD") != -1)
// 	{
// 		value = env_get(shell->env, "OLDPWD");
// 		if (!value)
// 		{
// 			printf(RED"ERROR: FAILED ENV_GET OLDPWD"RESET);
// 			exit(EXIT_FAILURE);
// 		}
// 		// shell->old_dir = ft_strdup(value);
// 		free(value);
// 	}
// 	else
// 		shell->old_dir = ft_strdup(dir);
// 	if (!shell->old_dir || !shell->cur_dir)
// 	{
// 		printf(RED"ERROR: DIR_INIT FAILED"RESET);
// 		exit(EXIT_FAILURE);
// 	}
// }

bool	shell_init(t_shell *shell, char **envp)
{
	env_init(shell, envp);
	shell->cmd_list = NULL;
	shell->pid = -1;
	shell->has_error = false;
	shell->last_exitcode = 0;
	rl_variable_bind("enable-bracketed-paste", "off");
	return (SUCCESS);
}
