#ifndef EXPANDER_H
# define EXPANDER_H

# include "minishell.h"

char	*replace_env_var(char *input, char **env, int lastexitcode);
char	*extract_var_name(char *input);
char	*expand_variables(char *input, char **env, int lastexitcode);

#endif /* EXPANDER_H */