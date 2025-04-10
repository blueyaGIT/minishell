/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalbano <dalbano@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 14:40:02 by dalbano           #+#    #+#             */
/*   Updated: 2025/04/10 14:40:03 by dalbano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "minishell.h"

int	ft_exec(t_shell *shell);
int	exec_local(t_shell *shell, t_command *cmd, char **args);
int	exec_sys(t_shell *shell, t_command *cmd);
int	exec_builtin(t_shell *shell, t_command *instr);
int	prep_cmd(t_shell *shell, t_command *cmd);
int	make_children(t_shell *shell);

#endif /* EXEC_H */