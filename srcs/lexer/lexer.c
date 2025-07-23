#include "minishell.h"

static bool	is_redirection(char c)
{
	if (c == '<' || c == '>')
		return (true);
	return (false);
}

static bool	before_is_word(char *input, int i)
{
	unsigned char	c;

	if (i <= 0)
		return (false);
	c = (unsigned char)input[i - 1];
	if (ft_isalnum(c) || c == '_')
		return (true);
	return (false);
}

static bool	after_is_word(char *input, int i)
{
	unsigned char	c;

	if (input[i + 1] == '\0')
		return (false);
	c = (unsigned char)input[i + 1];
	if (ft_isalnum(c) || c == '_')
		return (true);
	return (false);
}

static bool	is_empty_quote(char *input, int i)
{
	char	c;

	c = input[i];
	if ((c == '\'' || c == '\"') && input[i + 1] == c)
	{
		if (before_is_word(input, i) || after_is_word(input, i))
			return (false);
		else
			return (true);
	}
	return (false);
}

t_token	*lexer(char *input, t_shell *shell)
{
	t_token	*token;
	int		i;
	char	*temp;

	token = NULL;
	i = 0;
	if (!valid_input(input))
		return (NULL);
	temp = handle_env(shell);
	if (!temp)
		return (NULL);
	input = temp;
	while (input[i])
	{
		if (ft_isspace(input[i]))
			i++;
		else if (input[i] == '|')
			tokenize_pipe(&token, &i);
		else if (is_redirection(input[i]))
			tokenize_redirection(&token, input, &i);
		else if (is_empty_quote(input, i))
			handle_empty_quote(&token, &i);
		else
			tokenize_word(&token, input, &i);
	}
	tokenize_word_token(token);
	free(temp);
	return (token);
}
