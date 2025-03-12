#ifndef ENV_H
# define ENV_H

# include "minishell.h"

char	*env_get(char **env, char *key);
int		env_idx(char **env, char *key);
#endif /* ENV_H */