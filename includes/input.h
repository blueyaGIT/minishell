#ifndef INPUT_H
# define INPUT_H

# include "minishell.h"

char	*handle_input(char *input, t_shell *shell);
bool	valid_input(const char *input);
char	*handle_env(t_shell *shell);
char	*handle_dollar_exp(char *input_dup, int start, int *i, t_shell *shell);
char	*handle_tilde_exp(char *dup, int start, int *i, t_shell *shell);
char	*replace_with_value(char *input, int start, int end, char *value);

#endif