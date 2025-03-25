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
	while (shell->tokens[i])
	{
		tmp_token = malloc(sizeof(t_token));
		if (!tmp_token)
			return ;
		tmp_token->token_value = shell->tokens[i];
		tmp_token->type = token_type(shell->tokens[i]);
		ft_lstadd_back(&shell->list, ft_lstnew((void *)tmp_token));
		i++;
	}
}

// char **ft_add_to_array(char **array, char *new_entry)
// {
//     int len = 0;
//     char **new_array;

//     while (array && array[len])
//         len++;
//     new_array = malloc((len + 2) * sizeof(char *));
//     if (!new_array)
//         return NULL;
//     if (array)
//         memcpy(new_array, array, len * sizeof(char *));
//     new_array[len] = strdup(new_entry);
//     new_array[len + 1] = NULL;
//     free(array);
//     return new_array;
// }

t_node *create_new_node(void)
{
    t_node *new_node = malloc(sizeof(t_node));
    if (!new_node)
        return NULL;
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

    // 1. Argument speichern
    if (!new_node->args)
        new_node->args = strdup(token->token_value);
    else
    {
        char *temp = ft_strjoin(new_node->args, " ");
        free(new_node->args);
        new_node->args = ft_strjoin(temp, token->token_value);
        free(temp);
    }

    // 2. Falls vorher ein Redirect war, speichere als Dateiname
    if (*prev_was_redirect)
    {
        new_node->filename = ft_add_to_array(new_node->filename, token->token_value);
    }

    // 3. Merken, ob dieser Token ein Redirect ist
    *prev_was_redirect = is_operator(token->token_value);

    *token_lst = (*token_lst)->next;
}


char **ft_add_to_array(char **array, char *new_entry)
{
    int len = 0;
    char **new_array;
    while (array && array[len])
        len++;
    new_array = malloc((len + 2) * sizeof(char *));
    if (!new_array)
        return NULL;
    if (array)
        memcpy(new_array, array, len * sizeof(char *));
    
    new_array[len] = strdup(new_entry);
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

    bool prev_was_redirect = false; // 🟢 Merkt sich, ob der vorherige Token ein Redirect war

    while (*token_lst && ((t_token *)(*token_lst)->content)->type != PIPE)
    {
        t_token *token = (t_token *)(*token_lst)->content;
        if (token->type == WORD || token->type == DOUBLEQUOTED || token->type == SINGLEQUOTED)
            process_word_token(new_node, token_lst, &prev_was_redirect);
        else if (token->type == REDIR_IN || token->type == REDIR_OUT || token->type == HEREDOC || token->type == APPEND)
        {
            process_redirection_token(new_node, token_lst);
            prev_was_redirect = true;  // 🟢 Nach einem Redirect merken wir uns das
        }
        else
        {
            *token_lst = (*token_lst)->next;
            prev_was_redirect = false; // 🟢 Falls etwas anderes kommt, zurücksetzen
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
