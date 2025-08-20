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
	char	*input_man;

	token = NULL;
	i = 0;
	input_man = handle_input(input, shell);
	if (!input_man)
		return (NULL);
	while (input_man[i])
	{
		if (ft_isspace(input_man[i]))
			i++;
		else if (input_man[i] == '|')
			tokenize_pipe(&token, &i);
		else if (is_redirection(input_man[i]))
			tokenize_redirection(&token, input_man, &i);
		else if (is_empty_quote(input_man, i))
			handle_empty_quote(&token, &i);
		else
			tokenize_word(&token, input_man, &i);
	}
	tokenize_token(token);
	free(input_man);
	return (token);
}
