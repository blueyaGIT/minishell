#include "minishell.h"

static int	parse_word_content(char *input, int *i, char *word, int length)
{
	int		j;
	char	quote;
	int		is_assign;

	j = 0;
	is_assign = check_assignment(input, *i);
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
		else if (input[*i] == '=' && is_assign)
		{
			word[j++] = input[(*i)++];
			is_assign = 0;
		}
		else if (ft_isspace(input[*i]) && !is_assign)
			break ;
		else
			word[j++] = input[(*i)++];
	}
	word[j] = '\0';
	return (j);
}

void	tokenize_word(t_token **token, char *input, int *i)
{
	char			*word;
	int				length;
	int				written;
	t_token_type	type;

	length = calc_word_length_with_assignment(input, *i);
	word = (char *)malloc(length + 1);
	if (!word)
		return ;
	written = parse_word_content(input, i, word, length);
	if (written < 0)
	{
		free(word);
		return ;
	}
	if (check_assignment(word, 0))
		type = ASSIGNMENT;
	else
		type = T_WORD;
	token_add_back(token, new_token(type, word));
}
