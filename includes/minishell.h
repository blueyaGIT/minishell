

#ifndef MINISHELL_H
# define MINISHELL_H

/* EXTERNAL INCLUDES */
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

/* INCLUDES */
# include "libft/libft.h"
# include "shell.h"
# include "builtin.h"
# include "debug.h"
# include "env.h"
# include "exec.h"
# include "error.h"
# include "format.h"
# include "io.h"
# include "parsing.h"
# include "pipes.h"
# include "signals.h"
# include "utils.h"

/* READLINE INCLUDES */
# include <readline/history.h>
# include <readline/readline.h>

extern volatile sig_atomic_t	g_ecode;

# define TEST printf

# define PROMPT "\033[38;5;168m\033[1m🧚>$ \033[0m"

# define STDIN 0
# define STDOUT 1
# define STDERR 2

# define HEREDOC_FILE "/tmp/.minishell_heredoc_"

# define SUCCESS true
# define FAIL false

# ifndef DEBUG
#  define DEBUG 0
# endif

#endif /* MINISHELL_H */