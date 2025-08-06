#ifndef IO_H
# define IO_H

# include "minishell.h"

bool	check_io(t_redir *io, bool temp);
bool	refresh_io(t_redir *io);
void	init_redir(t_command *cmd);
void	fix_redir(t_shell *shell);
int		open_heredoc_temp(char *temp_file);
void	read_heredoc_input(t_shell *shell, int temp_fd);
void	do_heredoc(t_shell *shell, char *temp_file, int temp_fd);
void	handle_outfile(t_shell *shell);
void	process_next_heredocs(t_shell *shell, char *temp_file, int temp_fd);
void	handle_heredoc(t_shell *shell);
void	handle_infile(t_shell *shell);
#endif /* IO_H */