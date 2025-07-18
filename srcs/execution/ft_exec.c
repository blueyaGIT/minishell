#include "minishell.h"

static void	if_cmd_empty(t_shell *shell, t_command *cmd)
{
	int	i;

	if (!cmd || !cmd->cmd || cmd->cmd[0] == '\0')
	{
		if (cmd && cmd->args && cmd->args[1])
		{
			if (cmd->cmd)
				free(cmd->cmd);
			cmd->cmd = ft_strdup(cmd->args[1]);
			i = 1;
			while (cmd->args[i])
			{
				cmd->args[i - 1] = cmd->args[i];
				i++;
			}
			cmd->args[i - 1] = NULL;
			prep_cmd(shell, cmd);
			return ;
		}
		kill_shell(shell, EXIT_SUCCESS);
	}
}

int	prep_cmd(t_shell *shell, t_command *cmd)
{
	int	ecode;

	if (cmd && cmd->io && !check_io(cmd->io, true))
		kill_shell(shell, EXIT_FAILURE);
	if_cmd_empty(shell, cmd);
	fds_init(shell->cmd_list, cmd);
	if (!refresh_pipes(cmd->io))
		kill_shell(shell, EXIT_FAILURE);
	kill_fds(shell->cmd_list, false);
	if (ft_strchr(cmd->cmd, '/') == NULL)
	{
		ecode = exec_builtin(shell, cmd);
		if (ecode != 127)
			kill_shell(shell, ecode);
		ecode = exec_sys(shell, cmd);
		if (ecode != 127)
			kill_shell(shell, ecode);
	}
	ecode = exec_local(shell, cmd);
	kill_shell(shell, ecode);
	return (ecode);
}

int	exec_builtin(t_shell *shell, t_command *instr)
{
	int	temp;

	temp = 127;
	if (ft_strncmp(instr->cmd, "pwd", 4) == 0)
		temp = exec_pwd(shell);
	else if (ft_strncmp(instr->cmd, "env", 4) == 0)
		temp = exec_env(shell, instr->args);
	else if (ft_strncmp(instr->cmd, "exit", 5) == 0)
		temp = exec_exit(shell, instr->args);
	else if (ft_strncmp(instr->cmd, "cd", 3) == 0)
		temp = exec_cd(shell, instr->args);
	else if (ft_strncmp(instr->cmd, "echo", 5) == 0)
		temp = exec_echo(shell, instr->args);
	else if (ft_strncmp(instr->cmd, "export", 7) == 0)
		temp = exec_export(shell, instr->args);
	else if (ft_strncmp(instr->cmd, "unset", 6) == 0)
		temp = exec_unset(shell, instr->args);
	shell->last_exitcode = temp;
	return (temp);
}

static int	check_data(t_shell *shell)
{
	if (!shell || !shell->cmd_list)
		return (EXIT_SUCCESS);
	if (!shell->cmd_list->cmd)
	{
		if (shell->cmd_list->io && !check_io(shell->cmd_list->io, true))
			return (EXIT_FAILURE);
		return (EXIT_SUCCESS);
	}
	if (!pipes_init(shell))
		return (EXIT_FAILURE);
	return (127);
}

int	ft_exec(t_shell *shell)
{
	int	temp;

	temp = check_data(shell);
	if (temp != 127)
		return (temp);
	if (!shell->cmd_list->pipe_flag && !shell->cmd_list->prev
		&& check_io(shell->cmd_list->io, false))
	{
		refresh_pipes(shell->cmd_list->io);
		temp = exec_builtin(shell, shell->cmd_list);
		refresh_io(shell->cmd_list->io);
	}
	if (temp != 127)
		return (temp);
	return (make_children(shell));
}
