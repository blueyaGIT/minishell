#include "minishell.h"

void	reload_shell(t_shell *shell)
{
	if (shell && shell->input)
	{
		free(shell->input);
		shell->input = NULL;
	}
	if (shell && shell->token)
		free_token(shell->token);
	if (shell && shell->tokens)
		ft_free_arr(shell->tokens);
	if (shell && shell->cmd_list)
	{
		kill_pipes(shell->cmd_list, NULL);
		ft_free_command(shell->cmd_list);
	}
}

void	ft_free_shell(t_shell *shell)
{
	if (shell && shell->input)
	{
		free(shell->input);
		shell->input = NULL;
	}
	if (shell && shell->token)
		free_token(shell->token);
	if (shell && shell->tokens)
		ft_free_arr(shell->tokens);
	if (shell && shell->cmd_list)
	{
		kill_pipes(shell->cmd_list, NULL);
		ft_free_command(shell->cmd_list);
	}
	if (shell && shell->env)
		ft_free_env(shell->env);
	rl_clear_history();
}

t_shell	*get_shell(void)
{
	static t_shell	shell;

	return (&shell);
}
