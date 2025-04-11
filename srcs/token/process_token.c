# include "minishell.h"

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