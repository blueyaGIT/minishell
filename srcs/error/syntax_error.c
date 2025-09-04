#include "minishell.h"

int	print_error(const char *message, t_shell *shell)
{
	(ft_fprintf(STDERR_FILENO, "%s\n", message));
	set_exit_code(shell, 2);
	return (1);
}

int	syntax_error(const char *str, t_shell *shell)
{
	int	i;
	int	piped_already;
	int	found_word;

	i = 0;
	piped_already = 0;
	found_word = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '|')
		{
			if (str[i + 1] == '|')
				return (print_error("syntax: unexpected tk '||'\n", shell));
			if (piped_already || !found_word)
				return (print_error("syntax: unexpected tk '|'\n", shell));
			piped_already = 1;
		}
		else if (str[i] != ' ')
		{
			found_word = 1;
			piped_already = 0;
		}
		i++;
	}
	return (set_exit_code(shell, 0), 0);
}

int	check_unclosed_quotes(const char *input, t_shell *shell)
{
	int	single_quotes;
	int	double_quotes;

	single_quotes = 0;
	double_quotes = 0;
	while (*input)
	{
		if (*input == '\'')
			single_quotes = !single_quotes;
		else if (*input == '"')
			double_quotes = !double_quotes;
		input++;
	}
	if (single_quotes || double_quotes)
	{
		(ft_printf(RED "minishell: syntax error: unclosed quote\n" RESET));
		set_exit_code(shell, 2);
		return (1);
	}
	set_exit_code(shell, 0);
	return (0);
}

int	check_redirect_syntax(const char *str, t_shell *shell)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if ((str[i] == '<' || str[i] == '>') && str[i + 1] == '\0')
		{
			(ft_printf(RED "minishell: syntax error"
					" near unexpected tk 'newline'\n" RESET));
			set_exit_code(shell, 2);
			return (1);
		}
		if ((str[i] == '<' && str[i + 1] == '<' && str[i + 2] == '<')
			|| (str[i] == '>' && str[i + 1] == '>' && str[i + 2] == '>'))
		{
			ft_printf(RED "minishell: syntax error"
				" near unexpected tk '%c'" RESET "\n",
				str[i]);
			set_exit_code(shell, 2);
			return (1);
		}
		i++;
	}
	set_exit_code(shell, 0);
	return (0);
}
