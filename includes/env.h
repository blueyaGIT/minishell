/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalbano <dalbano@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 14:42:10 by dalbano           #+#    #+#             */
/*   Updated: 2025/09/08 14:42:13 by dalbano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "minishell.h"

typedef struct s_shell	t_shell;

void					env_init(t_shell *shell, char **envp);
char					*env_get(char **envp, char *key);
char					*get_env_value(const char *name, char **env);
int						env_idx(char **envp, char *key);
bool					set_env_var(t_shell *shell, char *key, char *value);
char					**refresh_env(t_shell *shell, int size);
char					**copy_env(char **env);
void					check_shlvl(t_shell *shell);

#endif /* ENV_H */