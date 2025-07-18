#include "minishell.h"

int	kill_shell(t_shell *shell, int ecode)
{
	if (shell)
	{
		if (shell->cmd_list && shell->cmd_list->io)
			kill_fds(shell->cmd_list, true);
		ft_free_shell(shell);
	}
	exit(ecode);
}
