# include "minishell.h"

void init_command_fields(t_command *cmd, t_node *node)
{
	cmd->command = NULL;
	cmd->filename = NULL;
	if (node->command)
		cmd->command = ft_strdup(node->command);
	if (node->filename && node->filename[0])
		cmd->filename = ft_strdup(node->filename[0]);
	cmd->args = split_args(node->args);
	cmd->io->infile = NULL;
	cmd->io->outfile = NULL;
	cmd->io->hrd_sep = NULL;
	cmd->io->hrd_flag = false;
}

void fill_redirections(t_command *cmd, t_node *node)
{
    int i = 0;
    while (node && node->redirections && node->redirections[i])
    {
        if (ft_strcmp(node->redirections[i], "<") == 0)
        {
            if (node->filename && node->filename[i])
                cmd->io->infile = ft_strdup(node->filename[i]);
        }
        else if (ft_strcmp(node->redirections[i], ">") == 0 || ft_strcmp(node->redirections[i], ">>") == 0)
        {
            if (node->filename && node->filename[i])
                cmd->io->outfile = ft_strdup(node->filename[i]);
        }
        else if (ft_strcmp(node->redirections[i], "<<") == 0)
        {
            if (node->filename && node->filename[i])
            {
                cmd->io->hrd_sep = ft_strdup(node->filename[i]);
                cmd->io->hrd_flag = true;
            }
        }
        i++;
    }
}

static void update_command_and_move(t_node **node, t_command **prev, t_command **head, t_command *curr)
{
    curr->prev = *prev;
    
    if ((*node)->command)
        curr->command = ft_strdup((*node)->command);
    if ((*node)->filename && (*node)->filename[0])
        curr->filename = ft_strdup((*node)->filename[0]);
    if ((*node)->args)
        curr->args = split_args((*node)->args);
    fill_redirections(curr, *node);
    if ((*node)->next)
        curr->pipe_flag = true;
    if (*prev)
        (*prev)->next = curr;
    else
        *head = curr;  
    *prev = curr;
    *node = (*node)->next;
}

t_command *convert_node_list_to_command_list(t_node *node)
{
    t_command *head = NULL;
    t_command *prev = NULL;
    t_command *curr;

    while (node)
    {
        curr = ft_calloc(sizeof(t_command), 1);
        if (!curr)
            return NULL;
        
        curr->io = ft_calloc(sizeof(t_redir), 1);
        if (!curr->io)
        {
            free(curr);
            return NULL;
        }
        update_command_and_move(&node, &prev, &head, curr);
    }
    return head;
}


char **split_args(char *args)
{
	char **res;
	int i;
	int p;
	int s;

	i = 0;
	p = 0;
	res = ft_calloc(sizeof(char *), (count_words(args) + 1));
	if (!res)
		return NULL;
	while (args[p])
	{
		while (args[p] == ' ')
			p++;
		if (args[p])
		{
			s = p;
			while (args[p] && args[p] != ' ')
				p++;
			res[i] = ft_substr(args, s, p - s);
			i++;
		}
	}
	res[i] = NULL;
	return res;
}


// void print_command_list(t_command *cmd_list)
// {
//     int i = 0;
//     while (cmd_list)
//     {
//         printf("┌───────────────────────────┐\n");
//         printf("│      Command Node %d       │\n", i);
//         printf("├───────────────────────────┤\n");
//         printf("│ command:     %s\n", cmd_list->command ? cmd_list->command : "NULL");
//         printf("│ filename:    %s\n", cmd_list->filename ? cmd_list->filename : "NULL");

//         printf("│ args:        ");
//         if (cmd_list->args)
//         {
//             int j = 0;
//             while (cmd_list->args[j])
//             {
//                 printf("%s ", cmd_list->args[j]);
//                 j++;
//             }
//             printf("\n");
//         }
//         else
//             printf("NULL\n");

//         printf("│ infile:      %s\n", cmd_list->io->infile ? cmd_list->io->infile : "NULL");
//         printf("│ outfile:     %s\n", cmd_list->io->outfile ? cmd_list->io->outfile : "NULL");
//         printf("│ hrd_sep:     %s\n", cmd_list->io->hrd_sep ? cmd_list->io->hrd_sep : "NULL");
//         printf("│ hrd_flag:    %s\n", cmd_list->io->hrd_flag ? "true" : "false");
//         printf("│ pipe_flag:   %s\n", cmd_list->pipe_flag ? "true" : "false");
//         printf("│ prev:        %p\n", (void *)cmd_list->prev);
//         printf("│ next:        %p\n", (void *)cmd_list->next);
//         printf("└───────────────────────────┘\n\n");

//         cmd_list = cmd_list->next;
//         i++;
//     }
// }

// void print_node_list(t_node *node_list)
// {
//     t_node *current = node_list;
//     int index = 0;
//     while (current)
//     {
//         printf("Node %d:\n", index);
//         printf(" command: %s \n", current->command);
//         printf("  args: %s\n", current->args ? current->args : "NULL");
//         printf("  filename: ");
//         if (current->filename)
//         {
//             int i = 0;
//             while (current->filename[i])
//             {
//                 printf("%s[%d]", current->filename[i], i);
//                 i++;
//             }
//         }
//         else
//         {
//             printf("NULL");
//         }
//         printf("\n");
//         printf("  redirections: ");
//         if (current->redirections)
//         {
//             int i = 0;
//             while (current->redirections[i])
//             {
//                 printf("%s[%d]", current->redirections[i], i);
//                 i++;
//             }
//         }
//         else
//         {
//             printf("NULL");
//         }
//         printf("\n\n");

//         current = current->next;
//         index++;
//     }
// }