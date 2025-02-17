#ifndef LAURA_H
# define LAURA_H

# include "minishell.h"

char **create_token(t_mini mini);
// void print_tokens(t_token **tokens);
void convert_tokens(t_mini *mini);
t_token_type	token_type(char *token);
void print_token_list(t_list *list);
// const char *token_type_to_string(t_token_type type);
// void collect_list_values(t_list *head, char *buffer, int buffer_size);

#endif /* LAURA_H */