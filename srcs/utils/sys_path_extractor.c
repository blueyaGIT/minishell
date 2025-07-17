

#include "minishell.h"

/**
 * build_full_command_path
	- Constructs a full path by concatenating a directory,
 *                           a slash, and a command.
 *
 * @param dir: The directory path.
 * @param cmd: The command name.
 *
 * @return A newly allocated string containing the full path,
	or NULL if allocation fails.
 */
static char	*build_full_command_path(char *dir, char *cmd)
{
	char	*full_path;

	full_path = ft_calloc(ft_strlen(dir) + ft_strlen(cmd) + 2, 1);
	if (!full_path)
		return (NULL);
	ft_strcpy(full_path, dir);
	ft_strcat(full_path, "/");
	ft_strcat(full_path, cmd);
	return (full_path);
}

/**
 * find_command_path
	- Finds the executable path of a command using the PATH environment variable.
 *
 * This function retrieves the PATH environment variable,
	splits it into directories, 
 * and for each directory,
	it builds the full command path using build_full_command_path().
 * It then checks if the command is executable. If so,
	it frees any allocated memory for the
 * directories array and returns the full command path.
 *
 * @param shell Pointer to the shell structure containing environment variables.
 * @param cmd   The command name to locate.
 *
 * @return A pointer to a newly allocated string with the command path if found,
	or NULL otherwise.
 */
char	*find_command_path(t_shell *shell, char *cmd)
{
	char	**paths;
	char	*full_path;
	int		i;

	if (!cmd || ft_strchr(cmd, '/'))
		return (ft_strdup(cmd));
	paths = ft_split(env_get(shell->env, "PATH"), ':');
	if (!paths)
		return (NULL);
	i = -1;
	while (paths[++i])
	{
		full_path = build_full_command_path(paths[i], cmd);
		if (access(full_path, X_OK) == 0)
			return (free(paths[i]), free(paths), full_path);
		free(full_path);
	}
	i = -1;
	while (paths[++i])
		free(paths[i]);
	free(paths);
	return (NULL);
}
