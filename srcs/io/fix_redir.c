#include "minishell.h"

void	do_heredoc(t_shell *shell, char *temp_file, int temp_fd, char *line)
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

void	fix_redir(t_shell *shell)
{
		char *line;
	char	*temp_file;
		int temp_fd;

	line = NULL;
	temp_fd = 0;
	temp_file = NULL;
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
    t_shell *current = shell;
    int	del_count;
	int	temp_del;

	if (shell->cmd_list->io->hrd_flag && shell->cmd_list->io->hrd_del)
	{
		del_count = 0;
		temp_del = 0;
		// Go to the last cmd_list
		while (current->cmd_list)
		{
			if(current->cmd_list->io->hrd_flag && current->cmd_list->io->hrd_del)
				del_count++;
			if (current->cmd_list->next)
				current->cmd_list = current->cmd_list->next;
			else
				break ;
		}
		while (temp_del < del_count)
		{
			unlink(temp_file);
			do_heredoc(current, temp_file, temp_fd, line);
			while (current)
			{
				if (current->cmd_list->io && current->cmd_list->io->hrd_flag && current->cmd_list->io->hrd_del)
				{
					// Found heredoc, set this cmd_list as current
					current->cmd_list = current->cmd_list;
					break;
				}
				current->cmd_list = current->cmd_list->next;
			}
			temp_del++;
		}
	}
}
