#ifndef PIPES_H
# define PIPES_H

# include "minishell.h"

bool	pipes_init(t_shell *shell);
bool	refresh_pipes(t_redir *io);
void	kill_fds(t_command *commands, bool temp);
void	kill_pipes(t_command *commands, t_command *temp);
bool	fds_init(t_shell *shell, t_command *cmd);

#endif /* PIPES_H */