/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalbano <dalbano@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 14:41:56 by dalbano           #+#    #+#             */
/*   Updated: 2025/06/25 15:11:55 by dalbano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "minishell.h"

void	ft_print_logo(char **envp);
void	extract_filepaths(const char *input);
void	ft_free_command(t_command *cmd);
void	ft_free_io(t_redir *io);
// void	ft_free_nodes(t_node *head);
// void	ft_free_tokens(t_token **lst);
bool	process_input(t_shell *shell);
bool	handle_syntax_and_exit(t_shell *shell);
bool	execute_commands(t_shell *shell);
char	*find_command_path(t_shell *shell, char *cmd);
void	ft_free_env(char **env);
bool	process_and_execute_input(t_shell *shell);

#endif /* UTILS_H */
