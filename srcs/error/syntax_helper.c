#include "minishell.h"

int	check_empty_input(const char *str, t_shell *shell)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
		{
			set_exit_code(shell, 0);
			return (0);
		}
		i++;
	}
	return (1);
}

void	set_exit_code(t_shell *shell, int code)
{
	if (shell)
		shell->last_exitcode = code;
}

int	run_syntax_checks(t_shell *shell)
{
	if (check_empty_input(shell->input, shell))
		return (1);
	if (check_unclosed_quotes(shell->input, shell))
		return (1);
	if (check_redirect_syntax(shell->input, shell))
		return (1);
	if (syntax_error(shell->input, shell))
		return (1);
	return (0);
}

static int	check_file_and_set_exit_code(const char *filename, int flags,
		t_shell *shell)
{
	int	fd;

	fd = open(filename, flags);
	if (fd == -1)
	{
		perror(filename);
		set_exit_code(shell, 1);
		return (1);
	}
	close(fd);
	return (0);
}

int	check_redirections(t_command *cmd, t_shell *shell)
{
	if (cmd->io->infile)
	{
		if (check_file_and_set_exit_code(cmd->io->infile, O_RDONLY, shell))
			return (1);
	}
	if (cmd->io->outfile)
	{
		if (check_file_and_set_exit_code(cmd->io->outfile, O_WRONLY, shell))
			return (1);
	}
	return (0);
}
