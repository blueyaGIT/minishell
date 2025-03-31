#ifndef ERROR_H
# define ERROR_H

# include "minishell.h"

int syntax_error(const char *str, t_shell *shell);
int check_unclosed_quotes(const char *input, t_shell *shell);
void set_exit_code(t_shell *shell, int error_type);
int run_syntax_checks(t_shell *shell);
int check_empty_input(const char *str, t_shell *shell);
int check_redirect_syntax(const char *str, t_shell *shell);
#endif /* ERROR_H */