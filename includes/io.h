#ifndef IO_H
# define IO_H

# include "minishell.h"

bool	check_io(t_redir *io, bool temp);
bool	refresh_io(t_redir *io);
void	init_redir(t_command *cmd);
void	fix_redir(t_shell *shell);

#endif /* IO_H */