#include "../../includes/minishell.h"

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
 array into the linekd list and adding the ENUM Type */
void	convert_tokens(t_mini *mini)
{
	t_token	*tmp_token;
	int		i;

	i = 0;
	while (mini->tokens[i])
	{
		tmp_token = malloc(sizeof(t_token));
		if (!tmp_token)
			return ;
		tmp_token->token_value = mini->tokens[i];
		tmp_token->type = token_type(mini->tokens[i]);
		ft_lstadd_back(&mini->list, ft_lstnew((void *)tmp_token));
		i++;
	}
}

// void enviroment_list(t_mini *mini)
// {
// 	t_node *tmp_token;

// 	while(*token_type != PIPE)
// 	{
// 		tmp_token = malloc(sizeof(t_node));
// 		if(!tmp_token)
// 			return ;
// 		tmp_token->args =
// 	}

// }
