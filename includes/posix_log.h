#ifndef POSIX_LOG_H
# define POSIX_LOG_H

# include "minishell.h"
# define LOG_PATH "./minishell.log"
# define BUFFER_SIZE 4096

int	write_log(const char *message);

#endif /* POSIX_LOG_H */