/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_shell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalbano <dalbano@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 13:47:02 by dalbano           #+#    #+#             */
/*   Updated: 2025/07/02 11:27:44 by dalbano          ###   ########.fr       */
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
        return ;
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
    {
        printf("Environment Variables: (null)\n");
    }
    printf("\n");

    // Print token
    if (shell->token)
    {
        printf("Tokens:\n");
        t_token *current = shell->token;
        i = 0;
        while (current)
        {
            printf("  [%d]: type=%d, value='%s'\n", i, 
                   current->type, 
                   current->value ? current->value : "null");
            current = current->next;
            i++;
        }
    }
    else
    {
        printf("Tokens: (null)\n");
    }
    printf("\n");

    // Print current input
    printf("Current Input: %s\n", shell->input ? shell->input : "null");
    // Print error state
    printf("Has Error: %s\n", shell->has_error ? "true" : "false");
    // Print exit code
    printf("Exit Code: %d\n", shell->last_exitcode);
    printf("------------------");
    printf("\n\n\n");
}
