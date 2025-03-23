#ifndef SHELL_H
# define SHELL_H

# include "minishell.h"

typedef struct s_shell
{
	char	**env;
	char	*cur_dir;
	char	*old_dir;
	char	*heredoc_file;
	int		heredoc_index;
	char	*history_file;
	bool	has_error;
	int		exit_code;
}			t_shell;

bool		shell_init(t_shell *shell, char **envp);
t_shell		*get_shell(void);
int			kill_shell(t_shell *shell, int close_shell);
#endif /* SHELL_H */