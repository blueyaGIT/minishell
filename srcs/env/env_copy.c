/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_copy.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalbano <dalbano@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 14:20:27 by dalbano           #+#    #+#             */
/*   Updated: 2025/04/07 17:22:10 by dalbano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char **copy_env(char **env)
{
    int i = 0;
    while (env[i])
        i++;

    char **env_copy = malloc((i + 1) * sizeof(char *));
    if (!env_copy)
        return (NULL);
    
    i = 0;
    while (env[i])
    {
        env_copy[i] = ft_strdup(env[i]);
        if (!env_copy[i])
        {
            while (i > 0)
                free(env_copy[--i]);
            free(env_copy);
            return (NULL);
        }
        i++;
    }
    env_copy[i] = NULL;
    return (env_copy);
}
