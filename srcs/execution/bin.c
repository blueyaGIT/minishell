/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalbano <dalbano@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 14:46:08 by dalbano           #+#    #+#             */
/*   Updated: 2025/09/08 14:46:09 by dalbano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_dir(char *cmd)
{
	struct stat	cmd_stat;

	ft_memset(&cmd_stat, 0, sizeof(cmd_stat));
	stat(cmd, &cmd_stat);
	return (S_ISDIR(cmd_stat.st_mode));
}

static char	**add_child_flag(char **envp)
{
	int		count;
	char	**new_envp;
	int		i;

	count = 0;
	while (envp[count])
		count++;
	new_envp = ft_calloc(count + 2, sizeof(char *));
	if (!new_envp)
		return (envp);
	i = 0;
	while (i < count)
	{
		new_envp[i] = envp[i];
		i++;
	}
	new_envp[i] = "MINISHELL_CHILD=1";
	new_envp[i + 1] = NULL;
	free(envp);
	return (new_envp);
}

int	exec_sys(t_shell *shell, t_command *cmd)
{
	char	**envp;
	int		err;

	if (!cmd->cmd || cmd->cmd[0] == '\0')
		return (127);
	if (is_dir(cmd->cmd))
		return (127);
	cmd->cpath = find_command_path(shell, cmd->cmd);
	if (cmd->cpath == NULL)
		return (127);
	cmd->args = ft_str_to_array_front(cmd->args, cmd->cmd);
	envp = build_envp(shell->env);
	envp = add_child_flag(envp);
	if (execve(cmd->cpath, cmd->args, envp) == -1)
	{
		err = errno;
		ft_free_arr(cmd->args);
		free(envp);
		return (err);
	}
	return (EXIT_FAILURE);
}

static int	validate_local_cmd(t_shell *shell, t_command *cmd)
{
	if (ft_strchr(cmd->cmd, '/') == NULL && env_idx(shell->env, "PATH")
		!= -1)
		return (127);
	if (access(cmd->cmd, F_OK) != 0)
		return (127);
	if (is_dir(cmd->cmd))
		return (126);
	if (access(cmd->cmd, X_OK) != 0)
		return (126);
	return (0);
}

int	exec_local(t_shell *shell, t_command *cmd)
{
	char	**envp;
	int		err;
	int		result;

	result = validate_local_cmd(shell, cmd);
	if (result != 0)
		return (result);
	cmd->cpath = find_command_path(shell, cmd->cmd);
	if (cmd->cpath == NULL)
		return (127);
	cmd->args = ft_str_to_array_front(cmd->args, cmd->cmd);
	envp = build_envp(shell->env);
	envp = add_child_flag(envp);
	if (execve(cmd->cpath, cmd->args, envp) == -1)
	{
		err = errno;
		ft_free_arr(cmd->args);
		free(envp);
		return (err);
	}
	return (EXIT_FAILURE);
}
