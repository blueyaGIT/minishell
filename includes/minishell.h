#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include "libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>

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

char **create_token(t_mini mini);
// void print_tokens(t_token **tokens);
void convert_tokens(t_mini *mini);
t_token_type	token_type(char *token);
void print_token_list(t_list *list);
// const char *token_type_to_string(t_token_type type);
// void collect_list_values(t_list *head, char *buffer, int buffer_size);

#endif /* MINISHELL_H */