#include "minishell.h"

void	fix_redir(t_shell *shell)
{
		char *line;
	char	*temp_file;
		int temp_fd;

	if (!shell || !shell->cmd_list || !shell->cmd_list->io)
		return ;
	if (shell->cmd_list->io->outfile)
	{
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
	if (shell->cmd_list->io->infile)
	{
		shell->cmd_list->io->fd_in = open(shell->cmd_list->io->infile,
				O_RDONLY);
		if (shell->cmd_list->io->fd_in == -1)
		{
			perror(shell->cmd_list->io->infile);
			shell->last_exitcode = 1;
		}
	}
	
	// Handle heredoc

	// // DEBUG
	// shell->cmd_list->io->hrd_flag = true;
	// shell->cmd_list->io->hrd_del = "stop";

	if (shell->cmd_list->io->hrd_flag && shell->cmd_list->io->hrd_del)
	{
		temp_file = "/tmp/heredoc_temp";
		// Create temporary heredoc file
		temp_fd = open(temp_file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (temp_fd == -1)
		{
			perror("heredoc temp file");
			shell->last_exitcode = 1;
			return ;
		}
		// Read lines until delimiter is found
		while (1)
		{
			fflush(stdout);
			line = readline(NULL);
			if (!line) // EOF (Ctrl+D)
				break ;
			// Check if line matches delimiter
			if (ft_strcmp(line, shell->cmd_list->io->hrd_del) == 0)
			{
				free(line);
				break ;
			}
			// Write line to temp file (echo functionality)
			ft_fprintf(temp_fd, "%s\n", line);
		}
		close(temp_fd);
		// Open temp file for reading and set as fd_in
		shell->cmd_list->io->fd_in = open(temp_file, O_RDONLY);
		if (shell->cmd_list->io->fd_in == -1)
		{
			perror("heredoc temp file read");
			shell->last_exitcode = 1;
		}
	}
}
