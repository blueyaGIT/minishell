/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalbano <dalbano@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 14:41:26 by dalbano           #+#    #+#             */
/*   Updated: 2025/04/12 14:28:30 by dalbano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

# include "minishell.h"

typedef enum e_token_type
{
	WORD,
	PIPE,
	RI,
	RO,
	HRD,
	APD,
	DQT,
	SQT,
}						t_token_type;

/*
only exampel for how we can sort the 
tokens in the list nothing in ore decided for now :)
*/
typedef struct s_node
{
	char				*command;
	char				*args;
	char				**filename;
	char				**rds;
	struct s_node		*next;
}						t_node;

//neuer Struct für command
typedef struct s_redir
{
	char				*infile;
	char				*outfile;
	char				*hrd_sep;
	bool				hrd_flag;
	int					fd_in;
	int					fd_out;
	int					stdin_backup;
	int					stdout_backup;
}						t_redir;

typedef struct s_command
{
	char				*command;
	char				*cpath;
	char				*filename;
	char				**args;
	bool				pipe_flag;
	int					*pipe_fd;
	t_redir				*io;
	struct s_command	*next;
	struct s_command	*prev;
}						t_command;

/*
tk value == the string witch is teh tk
tp == ENUM Value
*/
typedef struct s_token
{
	char				*token_value;
	t_token_type		tp;
	struct s_token		*next;
}						t_token;

typedef struct s_shell
{
	char				*input;
	char				**tokens;
	char				**env;
	t_node				*node;
	t_list				*list;
	t_command			*cmd_list;
	bool				has_error;
	int					last_exitcode;
	pid_t				pid;
}						t_shell;

bool					shell_init(t_shell *shell, char **envp);
t_shell					*get_shell(void);
int						kill_shell(t_shell *shell, int ecode);
void					refresh_shell(t_shell *shell);
void					ft_free_node(t_node **lst, void (*del)(void *));
void					ft_free_token(t_token **lst, void (*del)(void *));
void					ft_free_shell(t_shell *shell);
void					reload_shell(t_shell *shell);

#endif /* SHELL_H */