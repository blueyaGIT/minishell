/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalbano <dalbano@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 14:43:07 by dalbano           #+#    #+#             */
/*   Updated: 2025/09/24 17:56:57 by dalbano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

# include "minishell.h"

typedef enum e_token_type
{
	T_WORD,
	T_PIPE,
	T_REDIR_IN,
	T_REDIR_OUT,
	T_APPEND,
	T_HEREDOC,
	BUILTIN,
	COMMAND,
	ARGUMENT,
	ASSIGNMENT,
	FILENAME,
	HEREDOC_DELIM,
}						t_token_type;

typedef struct s_token
{
	t_token_type		type;
	char				*value;
	bool				is_echo_n;
	bool				is_removed;
	bool				is_echo;
	bool				add_space;
	struct s_token		*next;
	struct s_token		*prev;
}						t_token;

typedef struct s_redir_file
{
	char				*filename;
	t_token_type		type;
	struct s_redir_file	*next;
}						t_redir_file;

typedef struct s_redir
{
	t_redir_file		*infiles;
	t_redir_file		*outfiles;
	t_token_type		hrd_sep;
	char				*hrd_del;
	bool				hrd_flag;
	int					fd_in;
	int					fd_out;
	int					stdin_backup;
	int					stdout_backup;
}						t_redir;

typedef struct s_command
{
	char				*cmd;
	char				*cpath;
	char				**args;
	char				*filename;
	bool				is_echo;
	bool				is_echo_n;
	bool				pipe_flag;
	int					*pipe_fd;
	t_redir				*io;
	struct s_command	*next;
	struct s_command	*prev;
}						t_command;

typedef struct s_shell
{
	char				*input;
	char				**tokens;
	char				**env;
	t_token				*token;
	t_command			*cmd_list;
	bool				has_error;
	int					amount_here;
	int					last_exitcode;
	pid_t				pid;
}						t_shell;

bool					shell_init(t_shell *shell, char **envp);
t_shell					*get_shell(void);
int						kill_shell(t_shell *shell, int ecode);
void					refresh_shell(t_shell *shell);
void					ft_free_shell(t_shell *shell);
void					reload_shell(t_shell *shell);
void					ft_free_tok(t_shell *shell);

#endif /* SHELL_H */