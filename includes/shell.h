#ifndef SHELL_H
# define SHELL_H

# include "minishell.h"


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

/*
only exampel for how we can sort the tokens in the list nothing in ore decided for now :)
*/
typedef struct s_node
{
	char *command;
	char *args;
	char **filename;
	char **redirections;
	struct s_node *next;
} t_node;


//neuer Struct für command 
typedef struct s_redir
{
	char *infile;  //gleiche wie type=redir_IN | Wenn in t_token type=redir_IN -> token_value hier reinschreiben
	char *outfile; //gleiche nur mit redir_OUT
	char *hrd_sep; //token_value -> hierrein (">>")
	bool hrd_flag; //wenn heredoc vorhanden true
	int					fd_in; // ignorieren
	int					fd_out; // ignorieren
	int					stdin_backup; // ignorieren
	int					stdout_backup; // ignorieren
}						t_redir;

typedef struct s_command
{
	char *command;  //der command als string ("echo")
	char *filename; //der Dateiname as string ("test.txt")
	char **args;    //die Argumente fuer *command ({"-1", "-a", ...})
	bool pipe_flag; //wenn | dann flag auf true
	int *pipe_fd;   //ignorieren, wird von marzia gesetzt
	t_redir *io;    // io_file, heredoc hier drinnen
	struct s_command	*next;
	struct s_command	*prev;
}	t_command;

/*
token value == the string witch is teh token
type == ENUM Value
*/
typedef struct s_token
{
	char *token_value;
	t_token_type type;
	struct s_token *next;
}	t_token;


typedef struct s_shell
{
	char	*input;
	char	**tokens; 
	char	**env;
	t_node *node;
	t_list *list;
	t_command *cmd_list;

	char	*cur_dir;
	char	*old_dir;
	char	*heredoc_file;
	int		heredoc_index;
	char	*history_file;
	bool	has_error;
	int		last_exitcode;
	int		lastexitcode;
}			t_shell;

bool		shell_init(t_shell *shell, char **envp);
t_shell		*get_shell(void);
int			kill_shell(t_shell *shell, int close_shell);

#endif /* SHELL_H */