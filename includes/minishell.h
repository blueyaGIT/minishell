#ifndef MINISHELL_H
# define MINISHELL_H

/* EXTERNAL INCLUDES */
# include <dirent.h>
# include <fcntl.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <stdbool.h>
# include <errno.h>

/* INCLUDES */
# include "libft/libft.h"
# include "laura.h"
# include "posix_log.h"
# include "gcollector.h"
# include "format.h"
# include "builtin.h"
# include "signals.h"
# include "env.h"
# include "exec.h"
# include "utils.h"
# include "shell.h"

/* READLINE INCLUDES */
# include <readline/history.h>
# include <readline/readline.h>

extern volatile sig_atomic_t	g_sig;

#endif /* MINISHELL_H */