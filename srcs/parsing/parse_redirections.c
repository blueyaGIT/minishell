#include "minishell.h"

t_token *handle_redirection(t_token *token, t_command **command)
{
	t_command *current;

	if (!*command)
		command_add_back(command, new_command());
	current = command_last(*command);
	if(!current)
		return (NULL);
	if (!current->io)
	{
		current->io = malloc(sizeof(t_redir));
		if (!current->io)
			return (NULL);
		init_redir(current);
	}
	if (token->next && token->next->type == FILENAME && token->next->value)
	{
		current->filename = ft_strdup(token->next->value);
		if (!current->filename)
			return (NULL);
		if (token->type == T_REDIR_OUT || token->type == T_APPEND)
		{
			current->io->outfile = current->filename;
			current->io->hrd_sep = token->type;
		}
		else if (token->type == T_REDIR_IN)
		{
			current->io->infile = current->filename;
			current->io->hrd_sep = token->type;
		}
		else if (token->type == T_HEREDOC)
		{
			current->io->hrd_del = current->filename;
			current->io->hrd_flag = true;
			current->io->hrd_sep = token->type;
		}
	}
	token = token->next;
	return (token->next);
}
