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
# include "libft/libft.h"

extern volatile sig_atomic_t	g_sig;

typedef enum e_token_type
{
	WORD,  //0
	PIPE, //1
	REDIR_IN, //2
	REDIR_OUT, //3
	HEREDOC,    //4
	APPEND,  //5
	DOUBLEQUOTED, //6
	SINGLEQUOTED,    //7
}t_token_type;

typedef struct s_node
{
	char *args;
	char **filename;
	char **redirections;
} t_node;

typedef struct s_token
{
	char *token_value;
	t_token_type type;
	// struct s_token *next;
}	t_token;


typedef struct s_mini
{
	char *input;
	char **tokens;
	t_node node;
	t_list *list;
} t_mini;

/* INCLUDES */
# include "laura.h"
# include "format.h"
# include "posix_log.h"
# include "builtin.h"
# include "signals.h"
# include "env.h"
# include "exec.h"

/* READLINE INCLUDES */
# include <readline/history.h>
# include <readline/readline.h>

#endif /* MINISHELL_H */