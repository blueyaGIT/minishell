/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalbano <dalbano@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 14:43:11 by dalbano           #+#    #+#             */
/*   Updated: 2025/09/24 18:13:02 by dalbano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include "minishell.h"

void	init_signals(void);
void	refresh_signals(void);
void	init_heredoc_signals(void);
void	restore_signals_after_heredoc(void);
#endif /* SIGNALS_H */