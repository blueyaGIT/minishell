#ifndef TOKEN_H
# define TOKEN_H

# include "minishell.h"

void			print_token_list(t_list *list);
char			*create_quote_token(char **start);
char			*create_word_token(char **start);
char			**create_token(t_shell shell);
t_token_type	token_type(char *token);
void			convert_tokens(t_shell *shell);
// char			**ft_add_to_array(char **array, char *new_entry);
t_node			*create_new_node(void);
void			process_word_token(t_node *new_node, t_list **token_lst,
					bool *prev_was_redirect);
void			process_redirection_token(t_node *new_node, t_list **token_lst);
t_node			*parse_tokens(t_list **token_lst);
void			build_parsing_nodes(t_shell *shell);
void			print_node_list(t_node *node_list);
char			**ft_add_to_array(char **array, char *new_entry);
int				is_operator(char *token_value);
int				is_known_command(char *token_value);
t_command		*convert_node_list_to_command_list(t_node *node);
void			fill_redirections(t_command *cmd, t_node *node);
void			init_command_fields(t_command *cmd, t_node *node);
char			**split_args(char *args);
void			print_command_list(t_command *cmd_list);
int				count_words(const char *str);
#endif /* TOKEN_H */