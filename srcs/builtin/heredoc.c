#include "minishell.h"

static char	*generate_temp_filename(void)
{
	static int	counter = 0;
	char		*filename;
	char		*counter_str;

	counter_str = ft_itoa(counter++);
	if (!counter_str)
		return (NULL);
	filename = ft_strjoin("/tmp/heredoc_temp_", counter_str);
	free(counter_str);
	return (filename);
}

static int	open_heredoc_temp(char *temp_file)
{
	int	temp_fd;

	temp_fd = open(temp_file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (temp_fd == -1)
	{
		perror("heredoc temp file");
		return (-1);
	}
	return (temp_fd);
}

static void	read_heredoc_input(t_shell *shell, int temp_fd, char *delimiter)
{
	char	*line;

	(void)shell;
	while (1)
	{
		line = readline("");
		if (!line)
			break ;
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		ft_fprintf(temp_fd, "%s\n", line);
		free(line);
	}
}

static int	create_heredoc_file(t_shell *shell, char *delimiter, char *temp_file)
{
	int	temp_fd;

	temp_fd = open_heredoc_temp(temp_file);
	if (temp_fd == -1)
		return (EXIT_FAILURE);
	read_heredoc_input(shell, temp_fd, delimiter);
	close(temp_fd);
	return (EXIT_SUCCESS);
}

static int	setup_heredoc_input(t_shell *shell, char *temp_file)
{
	int	fd_in;

	fd_in = open(temp_file, O_RDONLY);
	if (fd_in == -1)
	{
		perror("heredoc temp file read");
		return (EXIT_FAILURE);
	}
	if (shell->cmd_list->io)
	{
		if (shell->cmd_list->io->fd_in != -1)
			close(shell->cmd_list->io->fd_in);
		shell->cmd_list->io->fd_in = fd_in;
	}
	return (EXIT_SUCCESS);
}

int	exec_heredoc(t_shell *shell, char *delimiter)
{
	char	*temp_file;
	int		result;

	if (!delimiter)
		return (EXIT_FAILURE);
	temp_file = generate_temp_filename();
	if (!temp_file)
		return (EXIT_FAILURE);
	result = create_heredoc_file(shell, delimiter, temp_file);
	if (result != EXIT_SUCCESS)
	{
		free(temp_file);
		return (result);
	}
	result = setup_heredoc_input(shell, temp_file);
	free(temp_file);
	if (result != EXIT_SUCCESS)
		return (result);
	return (EXIT_SUCCESS);
}
