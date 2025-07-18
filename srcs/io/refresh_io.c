#include "minishell.h"

bool	refresh_io(t_redir *io)
{
	bool	temp;

	temp = true;
	if (!io)
		return (temp);
	if (io->stdin_backup != -1)
	{
		if (dup2(io->stdin_backup, STDIN_FILENO) == -1)
			temp = FAIL;
		close(io->stdin_backup);
		io->stdin_backup = -1;
	}
	if (io->stdout_backup != -1)
	{
		if (dup2(io->stdout_backup, STDOUT_FILENO) == -1)
			temp = FAIL;
		close(io->stdout_backup);
		io->stdout_backup = -1;
	}
	return (temp);
}
