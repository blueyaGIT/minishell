#ifndef SHELL_H
# define SHELL_H

# include "minishell.h"

typedef struct s_shell
{
	char	**env;
	char	**exp;
	char	*history_file;
	char	*heredoc_file;
	int		heredoc_index;
	bool	has_error;
	char	*shell_dir;
	int		exit_code;
}			t_shell;

t_shell		*get_shell(void);
int			kill_shell(t_shell *shell, int close_shell);
#endif /* SHELL_H */