/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalbano <dalbano@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 14:42:39 by dalbano           #+#    #+#             */
/*   Updated: 2025/09/08 14:42:40 by dalbano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IO_H
# define IO_H

# include "minishell.h"

bool	check_io(t_redir *io, bool temp);
bool	refresh_io(t_redir *io);
void	init_redir(t_command *cmd);
void	fix_redir(t_shell *shell);
void	handle_outfile(t_shell *shell);
void	handle_infile(t_shell *shell);
#endif /* IO_H */