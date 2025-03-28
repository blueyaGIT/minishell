#ifndef UTILS_H
# define UTILS_H

# include "minishell.h"

void	ft_print_logo(char **envp);
void initialize_shell(t_shell *shell, char **envp);
void process_input(t_shell *shell);
int handle_syntax_and_exit(t_shell *shell);
void execute_commands( t_shell *shell);

#endif /* UTILS_H */
