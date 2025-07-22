#include "minishell.h"

void	init_redir(t_command *cmd)
{
	if (!cmd->io)
	{
		cmd->io = malloc(sizeof * cmd->io);
		if (!cmd->io)
			return ;
		cmd->io->infile = NULL;
		cmd->io->outfile = NULL;
		cmd->io->hrd_del = NULL;
		cmd->io->hrd_flag = false;
		cmd->io->fd_in = -1;
		cmd->io->fd_out = -1;
		cmd->io->stdin_backup = -1;
		cmd->io->stdout_backup = -1;
	}
}
