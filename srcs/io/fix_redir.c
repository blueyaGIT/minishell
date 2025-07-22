#include "minishell.h"

void	fix_redir(t_shell *shell)
{
	if (!shell || !shell->cmd_list || !shell->cmd_list->io)
		return ;
	if (shell->cmd_list->io->outfile)
	{
		if (shell->cmd_list->io->hrd_sep == T_APPEND)
			shell->cmd_list->io->fd_out = open(shell->cmd_list->io->outfile, O_CREAT | O_WRONLY | O_APPEND, 0644);
		else
			shell->cmd_list->io->fd_out = open(shell->cmd_list->io->outfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		
		if (shell->cmd_list->io->fd_out == -1)
		{
			perror(shell->cmd_list->io->outfile);
			shell->last_exitcode = 1;
		}
	}
	if (shell->cmd_list->io->infile)
	{
		shell->cmd_list->io->fd_in = open(shell->cmd_list->io->infile, O_RDONLY);
		if (shell->cmd_list->io->fd_in == -1)
		{
			perror(shell->cmd_list->io->infile);
			shell->last_exitcode = 1;
		}
	}
	
	// // Handle heredoc
	// if (shell->cmd_list->io->hrd_flag && shell->cmd_list->io->hrd_del)
	// {
	// 	// Heredoc handling - typically fd_in is set up during parsing
	// 	// This could involve creating a pipe and writing heredoc content
	// 	// Implementation depends on how heredoc is handled in your parser
	// }
}
