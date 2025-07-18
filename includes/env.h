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