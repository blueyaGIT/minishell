#include "minishell.h"

t_token	*handle_pipe(t_token *token, t_command **command)
{
	t_command	*new_cmd;

	new_cmd = new_command();
	if (!new_cmd)
		return (NULL);
	command_add_back(command, new_cmd);
	if (new_cmd->prev)
		new_cmd->prev->pipe_flag = true;
	return (token->next);
}

static void	add_arg(t_command *command, char *word)
{
	int		argc;
	char	**temp;
	int		i;

	i = 0;
	argc = 0;
	while (command->args && command->args[argc])
		argc++;
	temp = malloc(sizeof(char *) * (argc + 2));
	if (!temp)
		return ;
	while (i < argc)
	{
		temp[i] = command->args[i];
		i++;
	}
	temp[argc] = ft_strdup(word);
	if (!temp[argc])
	{
		free(temp);
		return ;
	}
	temp[argc + 1] = NULL;
	free(command->args);
	command->args = temp;
}

t_token	*handle_word(t_token *token, t_command **command)
{
	t_command	*current;

	if (!*command)
		command_add_back(command, new_command());
	current = command_last(*command);
	if (!current)
		return (NULL);
	if (!current->cmd)
	{
		current->cmd = ft_strdup(token->value);
		if (!current->cmd)
			return (NULL);
		if (token->is_echo && (!token->next || !is_word(token->next->type)))
			add_arg(current, "\n");
		if (token->is_echo_n)
			current->is_echo_n = true;
	}
	else
		add_arg(current, token->value);
	return (token->next);
}
