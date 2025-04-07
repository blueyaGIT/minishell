#ifndef UTILS_H
# define UTILS_H

# include "minishell.h"

void	ft_print_logo(char **envp);
void	extract_filepaths(const char *input);
void	ft_free_command(t_command **lst, void (*del)(void *));
void	ft_free_io(t_redir *io);
void	ft_free_nodes(t_node *head);
void	ft_free_tokens(t_token **lst);
void	process_input(t_shell *shell);
void	handle_syntax_and_exit(t_shell *shell);
void	execute_commands(t_shell *shell);
char	*find_command_path(t_shell *shell, char *cmd);
char	**add_str_to_array(char **array, char *str);

#endif /* UTILS_H */
