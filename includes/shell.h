#ifndef SHELL_H
# define SHELL_H

# include "minishell.h"

/**
 * typedef struct s_token
{
	char			*input;
	char			*input_backup;
	bool			var_check;
	int				type;
	int				status;
	bool			joined;
	struct s_token	*prev;
	struct s_token	*next;
}					t_token;

typedef struct s_redir
{
	char			*infile;
	char			*outfile;
	char			*heredoc_delimiter;
	bool			heredoc_quotes;
	int				fd_in;
	int				fd_out;
	int				stdin_backup;
	int				stdout_backup;
}					t_redir;

typedef struct s_cmd
{
	char			*cmd;
	char			*cmd_path;
	char			**args_list;
	bool			if_pipe;
	int				*pipe_fd;
	t_redir			*io;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}					t_cmd;
 */

typedef struct s_shell
{
	char	*input;
	char	**env;
	char	*cur_dir;
	char	*old_dir;
	char	*heredoc_file;
	int		heredoc_index;
	char	*history_file;
	bool	has_error;
	int		last_exitcode;
}			t_shell;

bool		shell_init(t_shell *shell, char **envp);
t_shell		*get_shell(void);
int			kill_shell(t_shell *shell, int close_shell);

#endif /* SHELL_H */