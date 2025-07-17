

#ifndef IO_H
# define IO_H

# include "minishell.h"

bool	check_io(t_redir *io, bool temp);
bool	refresh_io(t_redir *io);

#endif /* IO_H */