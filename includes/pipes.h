/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalbano <dalbano@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 14:43:01 by dalbano           #+#    #+#             */
/*   Updated: 2025/09/08 14:43:03 by dalbano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPES_H
# define PIPES_H

# include "minishell.h"

bool	pipes_init(t_shell *shell);
bool	refresh_pipes(t_redir *io);
void	kill_fds(t_command *commands, bool temp);
void	kill_pipes(t_command *commands, t_command *temp);
bool	fds_init(t_command *temp, t_command *cmd);

#endif /* PIPES_H */