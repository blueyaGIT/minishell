#ifndef LEXER_H
# define LEXER_H

# include "minishell.h"

t_token		*lexer(char *input, t_shell *shell);
void		init_token(t_token *token);
void		token_add_back(t_token **token, t_token *new);
t_token		*token_last(t_token *token);
t_token		*new_token(t_token_type type, char *value);
int			calc_word_length(char *ip, int i);
int			calc_word_length_with_assignment(char *input, int start);
void		tokenize_pipe(t_token **token, int *i);
void		tokenize_word(t_token **token, char *input, int *i);
void		tokenize_redirection(t_token **token, char *input, int *i);
void		tokenize_token(t_token *token);
bool		is_builtin(t_token *token);
void		handle_empty_quote(t_token **token, int *i);
bool		is_tok_sep(char c);
int			check_assignment(char *input, int start);

#endif