/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalbano <dalbano@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 02:11:24 by dalbano           #+#    #+#             */
/*   Updated: 2025/04/12 15:23:55 by dalbano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "minishell.h"

int	exec_env(t_shell *shell, char **args);
int	exec_exit(t_shell *shell, char **args);
int	exec_pwd(t_shell *shell);
int	exec_cd(t_shell *shell, char **args);
int	exec_echo(char **args);

#endif /* BUILTIN_H */