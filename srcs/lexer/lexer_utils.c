#include "minishell.h"

bool	is_tok_sep(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (true);
	return (false);
}

static void	calc_helper(int *length, int *i)
{
	(*i)++;
	(*length)++;
}

int	calc_word_length(char *ip, int i)
{
	int		length;
	char	quote;
	int		flag;

	flag = 0;
	length = 0;
	quote = '\0';
	while (ip[i] && !ft_isspace(ip[i]) && !is_tok_sep(ip[i]) && ip[i] != quote)
	{
		if (ip[i] == '\'' || ip[i] == '\"')
		{
			if (flag == 1)
				return (length);
			quote = ip[i];
			i++;
			while (ip[i] && ip[i] != quote)
				calc_helper(&length, &i);
		}
		else
		{
			flag = 1;
			calc_helper(&length, &i);
		}
	}
	return (length);
}

void	handle_output_redirection(t_token **token, char *input, int *i)
{
	if (input[*i + 1] == '>')
	{
		token_add_back(token, new_token(T_APPEND, ft_strdup(">>")));
		(*i) += 2;
	}
	else
	{
		token_add_back(token, new_token(T_REDIR_OUT, ft_strdup(">")));
		(*i)++;
	}
}

void	handle_input_redirection(t_token **token, char *input, int *i)
{
	if (input[*i + 1] == '<')
	{
		token_add_back(token, new_token(T_HEREDOC, ft_strdup("<<")));
		(*i) += 2;
	}
	else
	{
		token_add_back(token, new_token(T_REDIR_IN, ft_strdup("<")));
		(*i)++;
	}
}
