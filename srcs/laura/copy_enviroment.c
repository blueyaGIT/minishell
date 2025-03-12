#include "../../includes/minishell.h"

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
        env_copy[i] = strdup(env[i]);
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

void free_env(char **env)
{
    if (!env)
        return;
    int i = 0;
    while (env[i])
        free(env[i++]);
    free(env);
}