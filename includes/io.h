/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalbano <dalbano@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 14:42:39 by dalbano           #+#    #+#             */
/*   Updated: 2025/09/24 18:08:57 by dalbano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IO_H
# define IO_H

# include "minishell.h"

bool	check_io(t_redir *io);
bool	refresh_io(t_redir *io);
void	init_redir(t_command *cmd);
void	fix_redir(t_shell *shell);
void	handle_outfile(t_shell *shell);
void	handle_infile(t_shell *shell);
t_redir_file	*new_redir_file(char *filename, t_token_type type);
void	add_redir_file(t_redir_file **list, t_redir_file *new_file);
void	free_redir_files(t_redir_file *list);
#endif /* IO_H */