

#include "minishell.h"

// t_command *new_command(void)
// {
// 	t_command *new;
	
// 	new = malloc(sizeof(t_command));
// 	if (!new)
// 		return (NULL);
// 	init_command(new);
// 	return (new);
// }

// t_command	*command_last(t_command *command)
// {
// 	if (!command)
// 		return (NULL);
// 	while (command->next)
// 		command = command->next;
// 	return (command);
// }
// void	command_add_back(t_command **command, t_command *new)
// {
// 	t_command *temp;
// 	if (!command || !new)
// 		return ;
// 	if (!*command)
// 	{
// 		*command = new;
// 		return ;
// 	}
// 	temp = command_last(*command);
// 	temp->next = new;
// 	new->prev = temp;
// }