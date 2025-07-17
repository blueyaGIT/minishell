#include "minishell.h"

// void print_shell(t_shell *shell)
// {
//     int i;

//     printf("\n\n\n");
//     if (!shell)
//     {
//         printf("Shell pointer is NULL.\n");
//         return ;
//     }

//     printf("Shell Information:\n");
//     printf("------------------\n");

//     // Print environment variables
//     if (shell->env)
//     {
//         printf("Environment Variables:\n");
//         i = 0;
//         while (shell->env[i])
//         {
//             printf("  [%d]: %s\n", i, shell->env[i]);
//             i++;
//         }
//     }
//     else
//     {
//         printf("Environment Variables: (null)\n");
//     }
//     printf("\n");

//     // Print token
//     if (shell->token)
//     {
//         printf("Tokens:\n");
//         t_token *current = shell->token;
//         i = 0;
//         while (current)
//         {
//             printf("  [%d]: type=%d, value='%s'\n", i, 
//                    current->type, 
//                    current->value ? current->value : "null");
//             current = current->next;
//             i++;
//         }
//     }
//     else
//     {
//         printf("Tokens: (null)\n");
//     }
//     printf("\n");

//     // Print commands
//     if (shell->cmd_list)
//     {
//         printf("Commands:\n");
//         t_command *current_cmd = shell->cmd_list;
//         i = 0;
//         while (current_cmd)
//         {
//             printf("  [%d]: cmd='%s'\n", i, 
//                    current_cmd->cmd ? current_cmd->cmd : "null");
            
//             if (current_cmd->args)
//             {
//                 printf("       args: ");
//                 int j = 0;
//                 while (current_cmd->args[j])
//                 {
//                     printf("'%s' ", current_cmd->args[j]);
//                     j++;
//                 }
//                 printf("\n");
//             }
//             else
//             {
//                 printf("       args: (null)\n");
//             }
            
//             printf("       pipe_flag: %s\n", current_cmd->pipe_flag ? "true" : "false");
//             printf("       filename: %s\n", current_cmd->filename ? current_cmd->filename : "null");
//             printf("       cpath: %s\n", current_cmd->cpath ? current_cmd->cpath : "null");
            
//             if (current_cmd->io)
//             {
//                 printf("       I/O redirections:\n");
//                 printf("         infile: %s\n", current_cmd->io->infile ? current_cmd->io->infile : "null");
//                 printf("         outfile: %s\n", current_cmd->io->outfile ? current_cmd->io->outfile : "null");
//                 printf("         hrd_sep: %s\n", current_cmd->io->hrd_sep ? current_cmd->io->hrd_sep : "null");
//                 printf("         hrd_flag: %s\n", current_cmd->io->hrd_flag ? "true" : "false");
//             }
            
//             current_cmd = current_cmd->next;
//             i++;
//         }
//     }
//     else
//     {
//         printf("Commands: (null)\n");
//     }
//     printf("\n");

//     // Print current input
//     printf("Current Input: %s\n", shell->input ? shell->input : "null");
//     // Print error state
//     printf("Has Error: %s\n", shell->has_error ? "true" : "false");
//     // Print exit code
//     printf("Exit Code: %d\n", shell->last_exitcode);
//     printf("------------------");
//     printf("\n\n\n");
// }

const char *token_type_to_str(int type)
{
	switch (type)
	{
		case T_REDIR_IN: return "T_REDIR_IN";
		case T_REDIR_OUT: return "T_REDIR_OUT";
		case T_APPEND: return "T_APPEND";
		case T_HEREDOC: return "T_HEREDOC";
		default: return "UNKNOWN";
	}
}

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

	// Print tokens
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

	// Print commands
	if (shell->cmd_list)
	{
		printf("Commands:\n");
		t_command *current_cmd = shell->cmd_list;
		i = 0;
		while (current_cmd)
		{
			printf("  [%d]: cmd='%s'\n", i, 
			       current_cmd->cmd ? current_cmd->cmd : "null");

			if (current_cmd->args)
			{
				printf("       args: ");
				int j = 0;
				while (current_cmd->args[j])
				{
					printf("'%s' ", current_cmd->args[j]);
					j++;
				}
				printf("\n");
			}
			else
			{
				printf("       args: (null)\n");
			}

			printf("       pipe_flag: %s\n", current_cmd->pipe_flag ? "true" : "false");
			printf("       filename: %s\n", current_cmd->filename ? current_cmd->filename : "null");
			printf("       cpath: %s\n", current_cmd->cpath ? current_cmd->cpath : "null");

			if (current_cmd->io)
			{
				printf("       I/O redirections:\n");
				printf("         infile: %s\n", current_cmd->io->infile ? current_cmd->io->infile : "null");
				printf("         outfile: %s\n", current_cmd->io->outfile ? current_cmd->io->outfile : "null");
				printf("         hrd_sep: %s\n", token_type_to_str(current_cmd->io->hrd_sep));
				printf("         hrd_flag: %s\n", current_cmd->io->hrd_flag ? "true" : "false");
			}

			current_cmd = current_cmd->next;
			i++;
		}
	}
	else
	{
		printf("Commands: (null)\n");
	}
	printf("\n");

	// Print current input
	printf("Current Input: %s\n", shell->input ? shell->input : "null");
	// Print error state
	printf("Has Error: %s\n", shell->has_error ? "true" : "false");
	// Print exit code
	printf("Exit Code: %d\n", shell->last_exitcode);
	printf("------------------\n\n\n");
}