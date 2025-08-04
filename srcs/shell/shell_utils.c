#include "minishell.h"

void	reload_shell(t_shell *shell)
{
    t_command	*current;
    t_command	*temp;

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
        current = shell->cmd_list;
        while (current->prev)
            current = current->prev;
        while (current)
        {
            temp = current->next;
            ft_free_command(current);
            current = temp;
        }
    }
}

void	ft_free_shell(t_shell *shell)
{
    t_command	*current;
    t_command	*temp;

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
        current = shell->cmd_list;
        while (current->prev)
            current = current->prev;
        while (current)
        {
            temp = current->next;
            ft_free_command(current);
            current = temp;
        }
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
