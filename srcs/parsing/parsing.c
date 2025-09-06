#include "minishell.h"

static int	calculate_heredoc_amount(t_token *token)
{
	int	amount;

	if (!token)
		return (0);
	amount = 0;
	while (token)
	{
		if (token->type == T_HEREDOC)
			amount++;
		token = token->next;
	}
	return (amount);
}

static void	add_pipes_after(t_token *token)
{
	t_token	*pipe_tok;

	if (!token)
		return ;
	pipe_tok = new_token(T_PIPE, ft_strdup("|"));
	if (!pipe_tok)
		return ;
	pipe_tok->next = token->next;
	if (token->next)
		token->next->prev = pipe_tok;
	token->next = pipe_tok;
	pipe_tok->prev = token;
}

static t_token	*added_heredoc_pipes(t_shell *shell, t_token *token)
{
	t_token	*current;

	if (!token)
		return (NULL);
	current = token;
	while (current)
	{
		if (current->type == T_HEREDOC && shell->amount_here > 0)
		{
			if (current->next && current->next->type == HEREDOC_DELIM)
				current = current->next;
			add_pipes_after(current);
			shell->amount_here--;
		}
		current = current->next;
	}
	return (token);
}

int	process_and_execute_input(t_shell *shell)
{
	t_token		*token;
	t_command	*command;

	token = lexer(shell->input, shell);
	if (!token)
		return (0);
	if (!valid_syntax(token))
	{
		free_token(token);
		return (0);
	}
	shell->amount_here = calculate_heredoc_amount(token);
	token = added_heredoc_pipes(shell, token);
	shell->token = token;
	command = parse_code(shell->token);
	if (!command && shell->token)
	{
		free_token(shell->token);
		shell->token = NULL;
		return (0);
	}
	shell->cmd_list = command;
	return (1);
}

t_command	*parse_code(t_token *token)
{
	t_command	*command;

	command = NULL;
	while (token)
	{
		if (token->type == T_PIPE)
			token = handle_pipe(token, &command);
		else if (is_redirection_token(token))
			token = handle_redirection(token, &command);
		else if (is_word(token->type))
			token = handle_word(token, &command);
		else
			return (NULL);
	}
	return (command);
}
