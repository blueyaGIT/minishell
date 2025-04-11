#include "minishell.h"

// /*debug zum drucekn von der Liste */
// void	print_token_list(t_list *list)
// {
// 	t_token	*token_data;

// 	while (list)
// 	{
// 		token_data = (t_token *)list->content;
// 		if (token_data)
// 			printf("Token: %-15s | Type: %d\n", token_data->token_value,
// 					token_data->type);
// 		list = list->next;
// 	}
// }
/**/
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

static char *get_next_token(char **start)
{
    char *token;

    while (**start == ' ')
        (*start)++;
    if (!**start)
        return NULL; 
    if (**start == '"' || **start == '\'')
        return create_quote_token(start);
    else if ((**start == '<' && (*start)[1] == '<') || (**start == '>' && (*start)[1] == '>'))
    {
        token = ft_strndup(*start, 2);
        *start += 2;  
        return token;
    }
    else if (**start == '|' || **start == '<' || **start == '>')
    {
        token = ft_strndup(*start, 1);
        (*start)++;
        return token;
    }
    else
        return create_word_token(start);
}

char **create_token(t_shell shell)
{
    int   num = 0;
    char  *start = shell.input;
    char  *token;

    shell.tokens = ft_calloc(sizeof(char *), ft_strlen(start) + 1);
    if (!shell.tokens)
        return NULL;
    while ((token = get_next_token(&start)) != NULL)
        shell.tokens[num++] = token;
    shell.tokens[num] = NULL; 
    
    return shell.tokens;
}