#include "../includes/minishell.h"

char	*create_quote_token(char **start)
{
	char	quote;
	char	*end;
	char	*token;

	quote = **start;
	(*start)++;
	end = *start;
	while (*end && *end != quote)
		end++;
	if (*end == quote)
		end++;
	token = ft_strndup((*start) - 1, end - (*start) + 1);
	*start = end;
	return (token);
}

char	*create_word_token(char **start)
{
	char	*end;
	char	*token;

	end = *start;
	while (*end && *end != '<' && *end != '>' && *end != '|' && *end != ' ')
		end++;
	token = ft_strndup(*start, end - *start);
	*start = end;
	return (token);
}
char	**create_token(t_mini mini)
{
	int		num;
	char	*start;

	num = 0;
	start = mini.input;
	mini.tokens = malloc(sizeof(char *) * ft_strlen(start));
	if (!mini.tokens)
		return (NULL);
	while (*start)
	{
		while (*start == ' ')
			start++;
		if(!*start)
			break;
		if (*start == '"' || *start == '\'')
			mini.tokens[num++] = create_quote_token(&start);
		else if ((*start == '<' && start[1] == '<') || (*start == '>'
				&& start[1] == '>'))
		{
			mini.tokens[num++] = ft_strndup(start, 2);
			start += 2;
		}
		else if (*start == '|' || *start == '<' || *start == '>')
		{
			mini.tokens[num++] = ft_strndup(start, 1);
			start++;
		}
		else
			mini.tokens[num++] = create_word_token(&start);
	}
	return (mini.tokens[num] = NULL, mini.tokens);
}
/*debug*/
// void	print_tokens(t_token **tokens)
// {
// 	int	i;

// 	i = 0;
// 	while (tokens[i])
// 	{
// 		printf("Token: %s Type: %s\n", tokens[i]->token_value,
// 			token_type_to_string(tokens[i]->type));
// 		i++;
// 	}
// }
/*bebug*/
// const char	*token_type_to_string(t_token_type type)
// {
// 	if (type == WORD)
// 		return ("WORD");
// 	if (type == PIPE)
// 		return ("PIPE");
// 	if (type == REDIR_IN)
// 		return ("REDIR_IN");
// 	if (type == REDIR_OUT)
// 		return ("REDIR_OUT");
// 	if (type == HEREDOC)
// 		return ("HEREDOC");
// 	if (type == APPEND)
// 		return ("APPEND");
// 	if (type == DOUBLEQUOTED)
// 		return ("DOUBLEQUOTED");
// 	if (type == SINGLEQUOTED)
// 		return ("SINGELQUOTED");
// 	return ("UNKNOWN");
// }
// t_token	**convert_tokens(char **tokens)
// {
// 	int		count;
// 	t_token	**new_tokens;
// 	int		i;

// 	count = 0;
// 	while (tokens[count])
// 		count++;
// 	new_tokens = malloc(sizeof(t_token *) * (count + 1));
// 	if (!new_tokens)
// 		return (NULL);
// 	i = 0;
// 	while (tokens[i])
// 	{
// 		new_tokens[i] = malloc(sizeof(t_token));
// 		if (!new_tokens[i])
// 			return (NULL);
// 		new_tokens[i]->token_value = tokens[i];
// 		new_tokens[i]->type = token_type(tokens[i]);
// 		i++;
// 	}
// 	new_tokens[i] = NULL;
// 	return (new_tokens);
// }


//alt
void convert_tokens(t_mini *mini)
{
	t_token	*tmp_token;
	int		i;

	i = 0;
	while (mini->tokens[i])
	{
		tmp_token = malloc(sizeof(t_token));
		if (!tmp_token)
			return;
		tmp_token->token_value = mini->tokens[i];
		tmp_token->type = token_type(mini->tokens[i]);
		ft_lstadd_back(&mini->list, ft_lstnew((void *)tmp_token));
		i++;
	}
}

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
