#include "minishell.h"

bool	shell_init(t_shell *shell, char **envp)
{
	env_init(shell, envp);
	shell->cmd_list = NULL;
	shell->pid = -1;
	shell->has_error = false;
	shell->last_exitcode = 0;
	shell->amount_here = 0;
	return (SUCCESS);
}
