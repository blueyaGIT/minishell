#ifndef TOKEN_H
# define TOKEN_H

# include "minishell.h"

void			print_token_list(t_list *list);
char			*create_quote_token(char **start);
char			*create_word_token(char **start);
char			**create_token(t_mini mini);
t_token_type	token_type(char *token);
void			convert_tokens(t_mini *mini);
char			**ft_add_to_array(char **array, char *new_entry);
t_node			*create_new_node(void);
void			process_word_token(t_node *new_node, t_list **token_lst);
void			process_redirection_token(t_node *new_node, t_list **token_lst);
t_node			*parse_tokens(t_list **token_lst);
void			build_parsing_nodes(t_mini *mini);
void			print_node_list(t_node *node_list);

#endif /* TOKEN_H */