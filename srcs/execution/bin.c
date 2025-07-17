

#include "minishell.h"

static bool	is_dir(char *cmd)
{
	struct stat	cmd_stat;

	ft_memset(&cmd_stat, 0, sizeof(cmd_stat));
	stat(cmd, &cmd_stat);
	return (S_ISDIR(cmd_stat.st_mode));
}

int	exec_sys(t_shell *shell, t_command *cmd)
{
	if (!cmd->cmd || cmd->cmd[0] == '\0')
		return (127);
	if (is_dir(cmd->cmd))
		return (127);
	cmd->cpath = find_command_path(shell, cmd->cmd);
	if (cmd->cpath == NULL)
		return (127);
	cmd->args = ft_str_to_array_front(cmd->args, cmd->cmd);
	printf("SYS\n");
	for (int i = 0; i < ft_arrlen(cmd->args); i++)
		printf("%s\n", cmd->args[i]);
	printf("Command_path: %s\n", cmd->cpath);
	if (execve(cmd->cpath, cmd->args, shell->env) == -1)
		return (errno);
	return (EXIT_FAILURE);
}

int	exec_local(t_shell *shell, t_command *cmd)
{
	if (ft_strchr(cmd->cmd, '/') == NULL && env_idx(shell->env, "PATH")
		!= -1)
		return (127);
	if (access(cmd->cmd, F_OK) != 0)
		return (printf(RED "ERROR: No such file or directory" RESET), 127);
	if (is_dir(cmd->cmd))
		return (printf(RED "ERROR: Command is a Directory" RESET), 126);
	if (access(cmd->cmd, F_OK | X_OK) != 0)
		return (printf(RED "ERROR: Permission denied" RESET), 126);
	cmd->cpath = find_command_path(shell, cmd->cmd);
	if (cmd->cpath == NULL)
	return (127);
	cmd->args = ft_str_to_array_front(cmd->args, cmd->cmd);
	if (execve(cmd->cpath, cmd->args, shell->env) == -1)
		return (errno);
	return (EXIT_FAILURE);
}
