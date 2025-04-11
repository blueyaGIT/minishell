#ifndef EXPANDER_H
# define EXPANDER_H

# include "minishell.h"

typedef struct s_expander {
    int i;
    int j;
    int in_single_quotes;
    int in_double_quotes;
} t_expander;


typedef struct s_expansion_context {
    char *input;        
    char **env;               
    char *new_str;            
    int buffer_size;          
    t_expander exp;           
    char exit_code_str[12];   
} t_expansion_context;

char	*replace_env_var(char *input, char **env, int lastexitcode);
char	*extract_var_name(char *input);
char	*expand_variables(char *input, char **env, int lastexitcode);

#endif /* EXPANDER_H */