/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalbano <dalbano@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 02:11:24 by dalbano           #+#    #+#             */
/*   Updated: 2025/04/12 17:20:41 by dalbano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "minishell.h"

int		exec_env(t_shell *shell, char **args);
int		exec_exit(t_shell *shell, char **args);
int		exec_pwd(t_shell *shell);
int		exec_cd(t_shell *shell, char **args);
int		exec_echo(char **args);
int		exec_export(t_shell *shell, char **args);
int		exec_unset(t_shell *shell, char **args);
char	*ft_strjoin_three(const char *s1, const char *s2, const char *s3);
int		is_valid_varname(const char *s);
int		update_existing_env(t_shell *shell, char *key, char *value);
int		add_new_env(t_shell *shell, char *key, char *value);
int		set_or_update_env(t_shell *shell, char *key, char *value);

#endif /* BUILTIN_H */