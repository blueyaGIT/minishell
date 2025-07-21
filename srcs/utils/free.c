#include "minishell.h"

void	ft_free_io(t_redir *io)
{
	if (!io)
		return ;
	refresh_io(io);
	if (io->hrd_sep)
	{
		unlink(io->infile);
		// ft_free_ptr(io->hrd_sep);
	}
	if (io->infile)
		ft_free_ptr(io->infile);
	if (io->outfile)
		ft_free_ptr(io->outfile);
	if (io)
		ft_free_ptr(io);
}

void	ft_free_env(char **env)
{
	int	i;

	i = 0;
	if (env)
	{
		while (env[i])
		{
			ft_free_ptr(env[i]);
			i++;
		}
		free(env);
		env = NULL;
	}
}

void	ft_free_command(t_command *cmd)
{
	int	i;

	i = 0;
	if (!cmd)
		return ;
	free(cmd->cmd);
	free(cmd->cpath);
	free(cmd->filename);
	if (cmd->args)
	{
		while (cmd->args[i])
		{
			free(cmd->args[i]);
			i++;
		}
		free(cmd->args);
	}
	ft_free_io(cmd->io);
	free(cmd);
}

void free_token(t_token *token)
{
	t_token *tmp;

	while (token)
	{
		tmp = token->next;
		if (token->value)
			free(token->value);
		free(token);
		token = tmp;
	}
}

static void free_command(t_command *command)
{
	int i;
	if (!command)
		return ;
	if (command->args)
	{
		i = 0;
		while (command->args)
		{
			free(command->args);
			i++;
		}
		free(command->args);
	}
	if (command->cmd)
		free(command->cmd);
	if (command->cpath)
		free(command->cpath);
	if (command->pipe_fd)
		free(command->pipe_fd);
	if (command->io)
		ft_free_io(command->io);
	free(command);
}

void free_command_list(t_command *command)
{
	t_command *current;
	t_command *next;
	current = command;
	while (current)
	{
		next = current->next;
		free_command(current);
		current = next;
	}
}
