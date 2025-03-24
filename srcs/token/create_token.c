#include "minishell.h"

/*debug zum drucekn von der Liste */
void	print_token_list(t_list *list)
{
	t_token	*token_data;

	while (list)
	{
		token_data = (t_token *)list->content;
		if (token_data)
			printf("Token: %-15s | Type: %d\n", token_data->token_value,
				token_data->type);
		list = list->next;
	}
}
/**/

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
		if (!*start)
			break ;
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




