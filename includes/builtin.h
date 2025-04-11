/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalbano <dalbano@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 02:11:24 by dalbano           #+#    #+#             */
/*   Updated: 2025/04/11 15:45:32 by dalbano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "minishell.h"

int	exec_env(t_shell *shell, char **args);
int	exec_exit(t_shell *shell, char **args);
int	exec_pwd(t_shell *shell);

#endif /* BUILTIN_H */