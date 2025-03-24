#ifndef LAURA_H
# define LAURA_H

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
	char *args;
	char **filename;
	char **redirections;
	struct s_node *next;
} t_node;

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

/*
input = the input from readline function
tokens = string with has all token strings inside
node = shoulde be int the future the node prom pipe to pipe
list = is the struct from libft with this i can use the ft_lstadd_back and the ft_lstnew function from libft
*/
typedef struct s_mini
{
	char *input;
	char **tokens;
	char **env;
	t_node *node;
	t_list *list;
} t_mini;

char **create_token(t_mini mini);
void convert_tokens(t_mini *mini);
t_token_type	token_type(char *token);
void print_token_list(t_list *list);
// void enviroment_list(t_list *list);
int syntax_error(const char *str);
void build_parsing_nodes(t_mini *mini);
char	*ft_strjoin_free(char *s1, char *s2);
char	**ft_add_to_array(char **array, char *new_entry);
void print_node_list(t_node *node_list);
t_node *create_new_node();
void process_word_token(t_node *new_node, t_list **token_lst);
t_node *parse_tokens(t_list **token_lst);

#endif /* LAURA_H */