#include "minishell.h"

char *replace_env_var(char *input, char **env, int last_exitcode)
{
    char *var_name;
    char *value;

    if (!input || input[0] != '$') 
        return strdup(input);
    
    if (strcmp(input, "$?") == 0) 
    {
        char *exit_code_str = malloc(12);
        if (!exit_code_str)
            return NULL;
        sprintf(exit_code_str, "%d", last_exitcode); 
        return exit_code_str;
    }


    var_name = input + 1; 
    value = get_env_value(var_name, env);

    if (value) 
        return value;
    else 
        return strdup("");
}

char *extract_var_name(char *input)
{
    int i = 0;

    if (!input || !input[i] || !(ft_isalpha(input[i]) || input[i] == '_'))
        return strdup(""); 

    while (input[i] && (ft_isalnum(input[i]) || input[i] == '_'))
        i++;

    return strndup(input, i); 
}

char *expand_variables(char *input, char **env, int last_exitcode)
{
    char *new_str = malloc(1000); 
    int i = 0, j = 0;
    int in_single_quotes = 0;
    int in_double_quotes = 0;
    char exit_code_str[12];

    sprintf(exit_code_str, "%d", last_exitcode);  // Exit-Code als String speichern

    while (input[i])
    {
        if (input[i] == '\'')
            in_single_quotes = !in_single_quotes; 
        else if (input[i] == '"')
            in_double_quotes = !in_double_quotes; 

        if (input[i] == '$' && !in_single_quotes) 
        {
            if (input[i + 1] == '?')  // Sonderfall: $? ersetzen
            {
                strcpy(new_str + j, exit_code_str);
                j += strlen(exit_code_str);
                i += 2;  // Überspringe `$?`
            }
            else
            {
                i++;
                char *var = extract_var_name(input + i); 
                char *value = get_env_value(var, env); 
                
                if (value) 
                {
                    strcpy(new_str + j, value);
                    j += strlen(value);
                }
                else 
                {
                    new_str[j++] = '$';
                    strcpy(new_str + j, var);
                    j += strlen(var);
                }

                i += strlen(var); 
                free(var);
                free(value);
            }
        }
        else
        {
            new_str[j++] = input[i++];
        }
    }
    new_str[j] = '\0';
    return new_str;
}
