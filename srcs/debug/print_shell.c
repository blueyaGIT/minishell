/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_shell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalbano <dalbano@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 13:47:02 by dalbano           #+#    #+#             */
/*   Updated: 2025/03/25 18:16:50 by dalbano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void print_shell(t_shell *shell)
{
    int i;

	printf("\n\n\n");
    if (!shell)
    {
        printf("Shell pointer is NULL.\n");
        return;
    }

    printf("Shell Information:\n");
    printf("------------------\n");

    // Print environment variables
    if (shell->env)
    {
        printf("Environment Variables:\n");
        i = 0;
        while (shell->env[i])
        {
            printf("  [%d]: %s\n", i, shell->env[i]);
            i++;
        }
    }
    else
        printf("Environment Variables: (null)\n");

	printf("\n");
    // Print current input
    printf("Current Input: %s\n", shell->input ? shell->input : "null");
    // Print current directory
    printf("Current Directory: %s\n", shell->cur_dir ? shell->cur_dir : "null");
    // Print previous/old directory
    printf("Old Directory: %s\n", shell->old_dir ? shell->old_dir : "null");
    // Print error state
    printf("Has Error: %s\n", shell->has_error ? "true" : "false");
    // Print exit code
    printf("Exit Code: %d\n", shell->last_exitcode);
    printf("------------------");
	printf("\n\n\n");
}
