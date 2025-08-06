#include "minishell.h"

int	open_heredoc_temp(char *temp_file)
{
	int	temp_fd;

	temp_fd = open(temp_file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (temp_fd == -1)
	{
		perror("heredoc temp file");
		g_ecode = 1;
	}
	return (temp_fd);
}

void	read_heredoc_input(t_shell *shell, int temp_fd)
{
	char	*line;

	while (1)
	{
		fflush(stdout);
		line = readline(NULL);
		if (!line)
			break ;
		if (ft_strcmp(line, shell->cmd_list->io->hrd_del) == 0)
		{
			free(line);
			break ;
		}
		ft_fprintf(temp_fd, "%s\n", line);
		free(line);
	}
}

void	do_heredoc(t_shell *shell, char *temp_file, int temp_fd)
{
	temp_file = "/tmp/heredoc_temp";
	temp_fd = open_heredoc_temp(temp_file);
	if (temp_fd == -1)
		return ;
	read_heredoc_input(shell, temp_fd);
	close(temp_fd);
	shell->cmd_list->io->fd_in = open(temp_file, O_RDONLY);
	if (shell->cmd_list->io->fd_in == -1)
	{
		perror("heredoc temp file read");
		g_ecode = 1;
	}
}

void	handle_outfile(t_shell *shell)
{
	if (!shell->cmd_list->io->outfile)
		return ;
	if (shell->cmd_list->io->hrd_sep == T_APPEND)
		shell->cmd_list->io->fd_out = open(shell->cmd_list->io->outfile,
				O_CREAT | O_WRONLY | O_APPEND, 0644);
	else
		shell->cmd_list->io->fd_out = open(shell->cmd_list->io->outfile,
				O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (shell->cmd_list->io->fd_out == -1)
	{
		perror(shell->cmd_list->io->outfile);
		shell->last_exitcode = 1;
	}
}
