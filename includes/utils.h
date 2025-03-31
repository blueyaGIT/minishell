#ifndef UTILS_H
# define UTILS_H

# include "minishell.h"

void	ft_print_logo(char **envp, char **argv);
void	extract_filepaths(const char *input);
void	ft_free_command(t_command **lst, void (*del)(void *));
void	ft_free_io(t_redir *io);
void	initialize_shell(t_shell *shell, char **envp);
void	process_input(t_shell *shell);
int		handle_syntax_and_exit(t_shell *shell);
void	execute_commands(t_shell *shell);

#endif /* UTILS_H */
