#include "minishell.h"

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

int	calc_word_length_with_assignment(char *input, int start)
{
	int		length;
	int		i;
	char	quote;
	int		is_assign;

	length = 0;
	i = start;
	is_assign = check_assignment(input, start);
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '\"')
		{
			quote = input[i++];
			while (input[i] && input[i] != quote)
				calc_helper(&length, &i);
			if (input[i] == quote)
				i++;
		}
		else if (ft_isspace(input[i]) && !is_assign)
			break ;
		else
			calc_helper(&length, &i);
	}
	return (length);
}
