/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalbano <dalbano@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 14:46:11 by dalbano           #+#    #+#             */
/*   Updated: 2025/09/08 14:46:12 by dalbano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	process_heredocs(t_shell *shell)
{
	t_command	*cmd;
	t_command	*original_cmd;

	cmd = shell->cmd_list;
	original_cmd = shell->cmd_list;
	while (cmd)
	{
		if (cmd->io && cmd->io->hrd_flag && cmd->io->hrd_del)
		{
			shell->cmd_list = cmd;
			if (exec_heredoc(shell, cmd->io->hrd_del) != EXIT_SUCCESS)
			{
				shell->cmd_list = original_cmd;
				return (EXIT_FAILURE);
			}
		}
		cmd = cmd->next;
	}
	shell->cmd_list = original_cmd;
	return (EXIT_SUCCESS);
}
