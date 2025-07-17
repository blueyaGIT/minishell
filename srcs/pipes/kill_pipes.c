

#include "minishell.h"

void	kill_pipes(t_command *commands, t_command *temp)
{
	while (commands)
	{
		if (commands != temp && commands->pipe_fd)
		{
			close(commands->pipe_fd[0]);
			close(commands->pipe_fd[1]);
		}
		commands = commands->next;
	}
}

void	kill_fds(t_command *commands, bool temp)
{
	if (commands->io)
	{
		if (commands->io->fd_in != -1)
			close(commands->io->fd_in);
		if (commands->io->fd_out != -1)
			close(commands->io->fd_out);
		if (temp)
			refresh_io(commands->io);
	}
	kill_pipes(commands, NULL);
}
