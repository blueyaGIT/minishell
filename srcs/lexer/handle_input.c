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

static int	is_assignment(char *input, int start)
{
	int	i;

	i = start;
	if (!ft_isalpha(input[i]) && input[i] != '_')
		return (0);
	while (input[i] && (ft_isalnum(input[i]) || input[i] == '_'))
		i++;
	return (input[i] == '=');
}

static int	parse_word_content(char *input, int *i, char *word, int length)
{
	int		j;
	char	quote;
	int		is_assign;

	j = 0;
	is_assign = is_assignment(input, *i);
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
			word[j++] = input[(*i)++];
		else if (ft_isspace(input[*i]) && !is_assign)
			break;
		else
			word[j++] = input[(*i)++];
	}
	word[j] = '\0';
	return (j);
}

static int	calc_word_length_with_assignment(char *input, int start)
{
	int		length;
	int		i;
	char	quote;
	int		is_assign;

	length = 0;
	i = start;
	is_assign = is_assignment(input, start);
	
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '\"')
		{
			quote = input[i++];
			while (input[i] && input[i] != quote)
			{
				length++;
				i++;
			}
			if (input[i] == quote)
				i++;
		}
		else if (ft_isspace(input[i]) && !is_assign)
			break;
		else
		{
			length++;
			i++;
		}
	}
	return (length);
}

void	tokenize_word(t_token **token, char *input, int *i)
{
	char		*word;
	int			length;
	int			written;
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
	if (is_assignment(word, 0))
		type = ASSIGNMENT;
	else
		type = T_WORD;
	
	token_add_back(token, new_token(type, word));
}