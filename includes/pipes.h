#ifndef PIPES_H
# define PIPES_H

# include "minishell.h"

bool	pipes_init(t_shell *shell);
bool	refresh_pipes(t_redir *io);

#endif /* PIPES_H */