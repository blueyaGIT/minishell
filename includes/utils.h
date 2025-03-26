#ifndef UTILS_H
# define UTILS_H

# include "minishell.h"

void	ft_print_logo(char **envp, char **argv);
void	extract_filepaths(const char *input);
void	ft_free_command(t_command **lst, void (*del)(void *));
void	ft_free_io(t_redir *io);

#endif /* UTILS_H */
