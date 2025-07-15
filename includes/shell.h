/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkloters <lkloters@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 14:41:26 by dalbano           #+#    #+#             */
/*   Updated: 2025/07/15 14:11:11 by lkloters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef SHELL_H
# define SHELL_H

# include "minishell.h"

typedef enum e_token_type
{
	T_WORD, // Befehle, Argumente, Dateinamen
	T_PIPE, // |
	T_REDIR_IN, // < infile
	T_REDIR_OUT, // >outfile
	T_APPEND, // >> outfile
	T_HEREDOC, // << temp file + infile
	BUILTIN,
	COMMAND,
	ARGUMENT,
	ASSIGNMENT,
	FILENAME,
	HEREDOC_DELIM,
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
	struct s_token	*prev;
}					t_token;


//neuer Struct für command
typedef struct s_redir
{
	char				*infile; //lilli
	char				*outfile; //lilli
	// char				*hrd_sep; //lilli welches zeichen
	t_token_type		hrd_sep;
	char				*hrd_del; //lilli wort nach <<
	bool				hrd_flag; //lilli gibt es heredoc
	int					fd_in;
	int					fd_out;
	int					stdin_backup;
	int					stdout_backup;
}						t_redir;

typedef struct s_command
{
	char				**args; // hello
	struct s_command	*next;
	struct s_command	*prev;
	char				*cmd; // echo
	bool				pipe_flag; // "wenn | im input flag = true" 1 | 0
	t_redir				*io;
	
	char				*filename; //lilli
	char				*cpath;
	int					*pipe_fd;
}						t_command;

typedef struct s_shell
{
	char				*input;
	char				**tokens;
	char				**env;
	t_token				*token;
	t_command			*cmd_list;
	bool				has_error;
	int					last_exitcode;
	pid_t				pid;
}						t_shell;

bool					shell_init(t_shell *shell, char **envp);
t_shell					*get_shell(void);
int						kill_shell(t_shell *shell, int ecode);
void					refresh_shell(t_shell *shell);
// void					ft_free_node(t_node **lst, void (*del)(void *));
// void					ft_free_token(t_token **lst, void (*del)(void *));
void					ft_free_shell(t_shell *shell);
void					reload_shell(t_shell *shell);

#endif /* SHELL_H */