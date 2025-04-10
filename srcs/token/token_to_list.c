#include "minishell.h"

/*adding the type of the token with teh ENUM code*/
t_token_type	token_type(char *token)
{
	if (!token)
		return (WORD);
	if (!token[0])
		return (WORD);
	if (ft_strcmp(token, "|") == 0)
		return (PIPE);
	if (ft_strcmp(token, "<") == 0)
		return (REDIR_IN);
	if (ft_strcmp(token, ">") == 0)
		return (REDIR_OUT);
	if (ft_strcmp(token, "<<") == 0)
		return (HEREDOC);
	if (ft_strcmp(token, ">>") == 0)
		return (APPEND);
	if (token[0] == '"' && token[strlen(token) - 1] == '"')
		return (DOUBLEQUOTED);
	if (token[0] == '\'' && token[strlen(token) - 1] == '\'')
		return (SINGLEQUOTED);
	return (WORD);
}
/*here i converting my tokens who are in the
 array into the lined list and adding the ENUM Type */
void	convert_tokens(t_shell *shell)
{
	t_token	*tmp_token;
	int		i;

	i = 0;
    if (!shell->tokens)
		return ;  // 🛡 Fail
	while (shell->tokens[i])
	{
        if (!shell->tokens[i])
        break;


		tmp_token = ft_calloc(sizeof(t_token), 1);
		if (!tmp_token)
			return ;
		tmp_token->token_value = shell->tokens[i];
		tmp_token->type = token_type(shell->tokens[i]);
		ft_lstadd_back(&shell->list, ft_lstnew((void *)tmp_token));
		i++;
	}
}

t_node *create_new_node(void)
{
    t_node *new_node = ft_calloc(sizeof(t_node), 1);
    if (!new_node)
        return NULL;
    new_node->command = NULL;
    new_node->args = NULL;
    new_node->filename = NULL;
    new_node->redirections = NULL;
    new_node->next = NULL;
    return new_node;
}

int is_known_command(char *token_value)
{
    if (strcmp(token_value, "echo") == 0)
        return 1;
    if (strcmp(token_value, "ls") == 0)
        return 1;
    if (strcmp(token_value, "cat") == 0)
        return 1;
    if (strcmp(token_value, "pwd") == 0)
        return 1;
    return 0;
}
int is_operator(char *token_value)
{
    if (strcmp(token_value, "<") == 0)
        return 1;
    if (strcmp(token_value, ">") == 0)
        return 1;
    if (strcmp(token_value, "<<") == 0)
        return 1;
    if (strcmp(token_value, ">>") == 0)
        return 1;
    if (strcmp(token_value, "|") == 0)
        return 1;
    return 0;
}



void process_word_token(t_node *new_node, t_list **token_lst, bool *prev_was_redirect)
{
    t_token *token = (t_token *)(*token_lst)->content;

    if (*prev_was_redirect)
    {
        new_node->filename = ft_add_to_array(new_node->filename, token->token_value);
        *prev_was_redirect = false;
    }
    else if (!new_node->command) 
    {
        new_node->command = ft_strdup(token->token_value); // LEAKS HERE: 9 bytes in 2 blocks are indirectly lost in loss record 5 of 66
    }
    else 
    {
        if (!new_node->args)
            new_node->args = ft_strdup(token->token_value);
        else
        {
            char *temp = ft_strjoin(new_node->args, " ");
            free(new_node->args);
            new_node->args = ft_strjoin(temp, token->token_value);
            free(temp);
        }
    }
    *token_lst = (*token_lst)->next;
}


char **ft_add_to_array(char **array, char *new_entry)
{
    int len = 0;
    char **new_array;
    while (array && array[len])
        len++;
    new_array = ft_calloc((len + 2), sizeof(char *));
    if (!new_array)
        return NULL;
    if (array)
        ft_memcpy(new_array, array, len * sizeof(char *));
    
    new_array[len] = ft_strdup(new_entry);
    new_array[len + 1] = NULL; 
    free(array);
    return new_array;
}


void process_redirection_token(t_node *new_node, t_list **token_lst)
{
    t_token *token = (t_token *)(*token_lst)->content;
    new_node->redirections = ft_add_to_array(new_node->redirections, token->token_value);
    *token_lst = (*token_lst)->next;
    if (*token_lst)
    {
        t_token *next_token = (t_token *)(*token_lst)->content;
        new_node->filename = ft_add_to_array(new_node->filename, next_token->token_value); 
        *token_lst = (*token_lst)->next;
    }
}

t_node *parse_tokens(t_list **token_lst)
{
    t_node *new_node = create_new_node();
    if (!new_node)
        return NULL;

    bool prev_was_redirect = false; 

    while (*token_lst && ((t_token *)(*token_lst)->content)->type != PIPE)
    {
        t_token *token = (t_token *)(*token_lst)->content;
        if (token->type == WORD || token->type == DOUBLEQUOTED || token->type == SINGLEQUOTED)
            process_word_token(new_node, token_lst, &prev_was_redirect);
        else if (token->type == REDIR_IN || token->type == REDIR_OUT || token->type == HEREDOC || token->type == APPEND)
        {
            process_redirection_token(new_node, token_lst);
            prev_was_redirect = true;  
        }
        else
        {
            *token_lst = (*token_lst)->next;
            prev_was_redirect = false; 
        }
    }
    return new_node;
}



void build_parsing_nodes(t_shell *shell)
{
    t_list *token_lst = shell->list;
    t_node *head_node = NULL;
    t_node *current_node = NULL;
    while (token_lst)
    {
        t_node *new_node = parse_tokens(&token_lst);
        if (!head_node)
            head_node = new_node;
        else
            current_node->next = new_node;
        current_node = new_node;
        if (token_lst && ((t_token *)token_lst->content)->type == PIPE)
            token_lst = token_lst->next;
    }
    shell->node = head_node;
}

/*debug function witch prints the linked list with the nodes out */

void print_node_list(t_node *node_list)
{
    t_node *current = node_list;
    int index = 0;
    while (current)
    {
        printf("Node %d:\n", index);
        printf(" command: %s \n", current->command);
        printf("  args: %s\n", current->args ? current->args : "NULL");
        printf("  filename: ");
        if (current->filename)
        {
            int i = 0;
            while (current->filename[i])
            {
                printf("%s[%d]", current->filename[i], i);
                i++;
            }
        }
        else
        {
            printf("NULL");
        }
        printf("\n");
        printf("  redirections: ");
        if (current->redirections)
        {
            int i = 0;
            while (current->redirections[i])
            {
                printf("%s[%d]", current->redirections[i], i);
                i++;
            }
        }
        else
        {
            printf("NULL");
        }
        printf("\n\n");

        current = current->next;
        index++;
    }
}

int count_words(const char *str)
{
	int count;
	int in_word;

	count = 0;
	in_word = 0;
	while (*str)
	{
		if (*str != ' ' && in_word == 0)
		{
			in_word = 1;
			count++;
		}
		else if (*str == ' ')
			in_word = 0;
		str++;
	}
	return count;
}


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
	int i;
	i = 0;
	while (node && node->redirections && node->redirections[i])
	{
		printf("DEBUG: i = %d\n", i);
		printf("  redirection = %s\n", node->redirections[i]);

		if (node->filename && node->filename[i])
			printf("  filename[%d] = %s\n", i, node->filename[i]);
		else
			printf("  filename[%d] = NULL\n", i);

		if (ft_strcmp(node->redirections[i], "<") == 0)
		{
			if (node->filename && node->filename[i])
				cmd->io->infile = ft_strdup(node->filename[i]);
		}
		else if ((ft_strcmp(node->redirections[i], ">") == 0
			|| ft_strcmp(node->redirections[i], ">>") == 0))
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

t_command *convert_node_list_to_command_list(t_node *node)
{
	t_command *head;
	t_command *prev;
	t_command *curr;

	head = NULL;
	prev = NULL;
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
		curr->prev = prev;
		if (node->command)
			curr->command = ft_strdup(node->command);
		if (node->filename && node->filename[0])
			curr->filename = ft_strdup(node->filename[0]);
		if (node->args)
			curr->args = split_args(node->args);
		fill_redirections(curr, node);
		if (node->next)
			curr->pipe_flag = true;
		if (prev)
			prev->next = curr;
		else
			head = curr;
		prev = curr;
		node = node->next;
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


void print_command_list(t_command *cmd_list)
{
    int i = 0;
    while (cmd_list)
    {
        printf("┌───────────────────────────┐\n");
        printf("│      Command Node %d       │\n", i);
        printf("├───────────────────────────┤\n");
        printf("│ command:     %s\n", cmd_list->command ? cmd_list->command : "NULL");
        printf("│ filename:    %s\n", cmd_list->filename ? cmd_list->filename : "NULL");

        printf("│ args:        ");
        if (cmd_list->args)
        {
            int j = 0;
            while (cmd_list->args[j])
            {
                printf("%s ", cmd_list->args[j]);
                j++;
            }
            printf("\n");
        }
        else
            printf("NULL\n");

        printf("│ infile:      %s\n", cmd_list->io->infile ? cmd_list->io->infile : "NULL");
        printf("│ outfile:     %s\n", cmd_list->io->outfile ? cmd_list->io->outfile : "NULL");
        printf("│ hrd_sep:     %s\n", cmd_list->io->hrd_sep ? cmd_list->io->hrd_sep : "NULL");
        printf("│ hrd_flag:    %s\n", cmd_list->io->hrd_flag ? "true" : "false");
        printf("│ pipe_flag:   %s\n", cmd_list->pipe_flag ? "true" : "false");
        printf("│ prev:        %p\n", (void *)cmd_list->prev);
        printf("│ next:        %p\n", (void *)cmd_list->next);
        printf("└───────────────────────────┘\n\n");

        cmd_list = cmd_list->next;
        i++;
    }
}