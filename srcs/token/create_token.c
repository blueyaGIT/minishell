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

char	**create_token(t_shell shell)
{
	int		num;
	char	*start;

	num = 0;
	start = shell.input;
	shell.tokens = malloc(sizeof(char *) * ft_strlen(start));
	if (!shell.tokens)
		return (NULL);
	while (*start)
	{
		while (*start == ' ')
			start++;
		if (!*start)
			break ;
		if (*start == '"' || *start == '\'')
			shell.tokens[num++] = create_quote_token(&start);
		else if ((*start == '<' && start[1] == '<') || (*start == '>'
				&& start[1] == '>'))
		{
			shell.tokens[num++] = ft_strndup(start, 2);
			start += 2;
		}
		else if (*start == '|' || *start == '<' || *start == '>')
		{
			shell.tokens[num++] = ft_strndup(start, 1);
			start++;
		}
		else
			shell.tokens[num++] = create_word_token(&start);
	}
	return (shell.tokens[num] = NULL, shell.tokens);
}




