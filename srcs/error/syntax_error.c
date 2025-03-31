#include "minishell.h"

int syntax_error(const char *str, t_shell *shell)
{
    int i = 0;
    int piped_already = 0;
    int found_word = 0;

    while (str[i] != '\0')
    {
        if (str[i] == '|')
        {
            if (str[i + 1] == '|')
            {
                (printf(RED"minishell: syntax error near unexpected token '||'\n"RESET));
                set_exit_code(shell, 2);
                return 1;
            }
            if (piped_already || !found_word)
            {
                (printf(RED"minishell: syntax error near unexpected token '|'\n"RESET));
                set_exit_code(shell, 2);
                return 1;
            }
            piped_already = 1;
        }
        else if (str[i] != ' ')
        {
            found_word = 1;
            piped_already = 0;
        }
        i++;
    }
    set_exit_code(shell, 0); 
    return 0;
}

int check_unclosed_quotes(const char *input, t_shell *shell)
{
    int single_quotes = 0;
    int double_quotes = 0;

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
        (printf(RED"minishell: syntax error: unclosed quote\n"RESET));
        set_exit_code(shell, 2); 
        return 1; 
    }
    set_exit_code(shell, 0); 
    return 0;
}

int check_redirect_syntax(const char *str, t_shell *shell)
{
	int i = 0;
	while (str[i])
	{
		if ((str[i] == '<' || str[i] == '>') && str[i + 1] == '\0')
		{
            (printf(RED"minishell: syntax error near unexpected token 'newline'\n"RESET));
			set_exit_code(shell, 2);
			return 1;
		}
		if ((str[i] == '<' && str[i + 1] == '<' && str[i + 2] == '<') ||
			(str[i] == '>' && str[i + 1] == '>' && str[i + 2] == '>'))
		{
            printf(RED"minishell: syntax error near unexpected token '%c'"RESET"\n", str[i]);
			set_exit_code(shell, 2);
			return 1;
		}
		i++;
	}
	set_exit_code(shell, 0);
	return 0;
}
int check_empty_input(const char *str, t_shell *shell)
{
	int i = 0;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
		{
			set_exit_code(shell, 0);
			return 0;
		}
		i++;
	}
    (printf(RED"minishell: syntax error: empty input\n"RESET));
	printf("minishell: syntax error: empty input\n");
	set_exit_code(shell, 2);
	return 1;
}


void set_exit_code(t_shell *shell, int code)
{
    if (shell)
        shell->last_exitcode = code;
}
int run_syntax_checks(t_shell *shell)
{
	if (check_empty_input(shell->input, shell))
		return 1;

	if (check_unclosed_quotes(shell->input, shell))
		return 1;

	if (check_redirect_syntax(shell->input, shell))
		return 1;

	if (syntax_error(shell->input, shell))
		return 1;

	return 0;
}
