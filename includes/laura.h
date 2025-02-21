#ifndef LAURA_H
# define LAURA_H

# include "minishell.h"

char **create_token(t_mini mini);
void convert_tokens(t_mini *mini);
t_token_type	token_type(char *token);
void print_token_list(t_list *list);
// void enviroment_list(t_list *list);


#endif /* LAURA_H */