

#include "minishell.h"

void	tokenize_redirection(t_token **token, char *input, int *i)
{
	if (input[*i] == '>')
		handle_output_redirection(token, input, i);
	else if (input[*i] == '<')
		handle_input_redirection(token, input, i);
}

void	tokenize_pipe(t_token **token, int *i)
{
	token_add_back(token, new_token(T_PIPE, ft_strdup("|")));
	(*i)++;
}

void	handle_empty_quote(t_token **token, int *i)
{
	token_add_back(token, new_token(T_WORD, ft_strdup("")));
	(*i) += 2;
}

static int	parse_word_content(char *input, int *i, char *word, int length)
{
	int		j;
	char	quote;

	j = 0;
	while (input[*i] && j < length)
	{
		if (input[*i] == '\'' || input[*i] == '\"')
		{
			quote = input[(*i)++];
			while (input[*i] && input[*i] != quote && j < length)
				word[j++] = input[(*i)++];
			if (input[*i] == quote)
				(*i)++;
		}
		else
			word[j++] = input[(*i)++];
	}
	word[j] = '\0';
	return (j);
}

void	tokenize_word(t_token **token, char *input, int *i)
{
	char	*word;
	int		length;
	int		written;

	length = calc_word_length(input, *i);
	printf("Length: %d\n", length);
	word = (char *)malloc(length + 1);
	if (!word)
		return ;
	written = parse_word_content(input, i, word, length);
	if (written < 0)
	{
		free(word);
		return ;
	}
	token_add_back(token, new_token(T_WORD, word));
}
