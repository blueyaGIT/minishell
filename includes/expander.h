/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalbano <dalbano@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 14:40:07 by dalbano           #+#    #+#             */
/*   Updated: 2025/04/10 14:40:08 by dalbano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "minishell.h"

char	*replace_env_var(char *input, char **env, int lastexitcode);
char	*extract_var_name(char *input);
char	*expand_variables(char *input, char **env, int lastexitcode);

#endif /* EXPANDER_H */