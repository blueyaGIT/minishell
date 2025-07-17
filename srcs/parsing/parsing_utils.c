

#include "minishell.h"

// void init_command(t_command *command)
// {
//    if (!command)
//    	return ;
//    command->args = NULL;
//    command->next = NULL;
//    command->prev = NULL;
//    command->cmd = NULL;
//    command->pipe_flag = false;
//    command->is_echo_option = false;
//    command->io = NULL;
//    command->filename = NULL;
//    command->cpath = NULL;
//    command->pipe_fd = NULL;
// }

// void init_redir(t_redir *redir)
// {
// 	if (!redir)
// 		return ;
// 	redir->infile = NULL;
// 	redir->outfile = NULL;
// 	// redir->hrd_sep = NULL;
// 	redir->hrd_del = NULL;
// 	redir->hrd_flag = false;
// }

// bool is_word(t_token_type type)
// {
// 	if (type == BUILTIN || type == COMMAND || type == ARGUMENT || type == ASSIGNMENT || type == FILENAME || type == HEREDOC_DELIM)
// 		return (true);
// 	return (false);
// }

// bool is_redirection_token(t_token *token)
// {
// 	if (token->type == T_APPEND || token->type == T_HEREDOC || token->type == T_REDIR_IN || token->type == T_REDIR_OUT)
// 		return (true);
// 	return (false);
// }