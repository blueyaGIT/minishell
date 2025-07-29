#include "minishell.h"

static bool	is_redirection(char c)
{
	if (c == '<' || c == '>')
		return (true);
	return (false);
}

static bool	is_empty_quote(char *input, int i)
{
	char	c;

	c = input[i];
	if ((c == '\'' || c == '\"') && input[i + 1] == c)
		return (true);
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
	return (free(temp), token);
}
