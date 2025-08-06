#include "minishell.h"

void	handle_infile(t_shell *shell)
{
	if (!shell->cmd_list->io->infile)
		return ;
	shell->cmd_list->io->fd_in = open(shell->cmd_list->io->infile, O_RDONLY);
	if (shell->cmd_list->io->fd_in == -1)
	{
		perror(shell->cmd_list->io->infile);
		shell->last_exitcode = 1;
	}
}

void	process_next_heredocs(t_shell *shell, char *temp_file, int temp_fd)
{
	t_command	*current;
	t_command	*original_cmd;

	current = shell->cmd_list->next;
	while (current && current->io)
	{
		if (current->io->hrd_flag && current->io->hrd_del)
		{
			temp_fd = open("/tmp/heredoc_temp", O_WRONLY | O_TRUNC);
			if (temp_fd != -1)
				close(temp_fd);
			original_cmd = shell->cmd_list;
			shell->cmd_list = current;
			do_heredoc(shell, temp_file, temp_fd);
			shell->cmd_list = original_cmd;
		}
		current = current->next;
	}
}

void	handle_heredoc(t_shell *shell)
{
	char	*temp_file;
	int		temp_fd;

	temp_fd = 0;
	temp_file = NULL;
	if (!(shell->cmd_list->io->hrd_flag && shell->cmd_list->io->hrd_del))
		return ;
	do_heredoc(shell, temp_file, temp_fd);
	process_next_heredocs(shell, temp_file, temp_fd);
}

void	fix_redir(t_shell *shell)
{
	if (!shell || !shell->cmd_list || !shell->cmd_list->io)
		return ;
	handle_outfile(shell);
	handle_infile(shell);
	handle_heredoc(shell);
}
