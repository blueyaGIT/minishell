/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalbano <dalbano@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 11:01:18 by dalbano           #+#    #+#             */
/*   Updated: 2025/04/01 16:11:04 by dalbano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * check_children - Waits for all child processes and returns the exit status.
 *
 * This function performs the following steps:
 *
 *  - Calls kill_fds() to clean up file descriptors associated with the command list.
 * 
 *  - Enters a loop that waits for any child process to finish using waitpid().
 * 
 *  - If the PID returned by waitpid() matches the shell's tracked PID, it stores the exit status.
 * 
 *  - Once all child processes have been reaped (when waitpid() returns -1 and errno is ECHILD), 
 *    it checks the stored status:
 * 		- If the child was terminated by a signal, returns 128 plus the signal number.
 *		- If the child exited normally, returns its exit code.
 *		- Otherwise, returns the raw exit status.
 *
 * @param shell: Pointer to the shell structure containing command list and process IDs.
 * @return The final exit status after interpreting the exit state(s) of the child processes.
 */
static int	check_children(t_shell *shell)
{
	pid_t	wpid;
	int		exit_status;
	int		temp;

	wpid = 0;
	temp = 0;
	kill_fds(shell->cmd_list, false);
	while (wpid != -1 || errno != ECHILD)
	{
		wpid = waitpid(-1, &exit_status, 0);
		if (wpid == shell->pid)
			temp = exit_status;
		continue ;
	}
	if (WIFSIGNALED(temp))
		exit_status = 128 + WTERMSIG(temp);
	else if (WIFEXITED(temp))
		exit_status = WEXITSTATUS(temp);
	else
		exit_status = temp;
	return (exit_status);
}

/**
 * make_children - Spawns child processes for each command and waits for their termination.
 *
 * This function performs the following steps:
 * 
 *   - Iterates over the linked list of commands stored in shell->cmd_list.
 * 
 *   - For each command:
 *       - Forks a new process.
 *       - If fork() fails, prints an error message and returns EXIT_FAILURE.
 *       - If in the child process (fork() returns 0), calls execute_command() to execute the command.
 * 
 *   - After processing all commands, calls check_children() to wait for all child processes
 *     to finish and to retrieve the final exit status.
 *
 * @param shell Pointer to the shell structure containing the command list and process IDs.
 *
 * @return The exit status determined by check_children(), or EXIT_FAILURE if a fork error occurs.
 */
int	make_children(t_shell *shell)
{
	t_command	*command;

	command = shell->cmd_list;
	while (shell->pid != 0 && command)
	{
		shell->pid = fork();
		if (shell->pid == -1)
			return (printf(RED"ERROR: FORK"RESET), EXIT_FAILURE);
		else if (shell->pid == 0)
			prep_cmd(shell, command);
		command = command->next;
	}
	return (check_children(shell));
}
