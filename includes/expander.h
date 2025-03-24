#ifndef EXPANDER_H
# define EXPANDER_H

# include "minishell.h"

char	*replace_env_var(char *input, char **env, int last_exitcode);
char	*extract_var_name(char *input);
char	*expand_variables(char *input, char **env, int last_exitcode);

#endif /* EXPANDER_H */