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

char *get_env_value(const char *name, char **env)
{
    int i = 0;
    
    while (env[i]) // Durchlaufe die Umgebungsvariablen
    {
        char *entry = env[i];
        int j = 0;

        while (entry[j] && entry[j] != '=') // Finde das '=' in der Variable
            j++;

        if (strncmp(entry, name, j) == 0 && name[j] == '\0') // Vergleiche Namen
            return strdup(entry + j + 1); // Rückgabe des Wertes nach '='

        i++;
    }
    return strdup(""); // Falls nicht gefunden, gib leeren String zurück
}

char *replace_env_var(char *input, char **env)
{
    char *var_name;
    char *value;

    if (!input || input[0] != '$') // Prüfen, ob es eine Variable ist
        return strdup(input);

    var_name = input + 1; // `$USER` -> `USER`
    value = get_env_value(var_name, env);

    if (value) // Falls gefunden, gib den Wert zurück
        return value;
    else // Falls nicht, gib einen leeren String zurück
        return strdup("");
}