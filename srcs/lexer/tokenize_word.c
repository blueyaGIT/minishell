/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_word.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkloters <lkloters@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 16:32:31 by lkloters          #+#    #+#             */
/*   Updated: 2025/07/09 10:44:16 by lkloters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static bool is_filename(t_token *prev)
// {
// 	if (!prev)
// 		return (false);
// 	if (prev->type == T_REDIR_IN || prev->type == T_REDIR_OUT || prev->type == T_APPEND)
// 		return (true);
// 	return (false);
// }

// static bool is_heredoc_delim(t_token *prev)
// {
// 	if (!prev)
// 		return (false);
// 	if (prev->type == T_HEREDOC)
// 		return (true);
// 	return (false);
// }

// static bool is_assignment(const char *token)
// {
//     int i;
// 	i = 0;
// 	if (!token || !strchr(token, '='))
//         return (false);
//     if (token[0] == '=')
//         return (false);
//     const char *equals = strchr(token, '=');
//     int name_len = equals - token;
//     while (i < name_len)
//     {
//         if (i == 0)
//         {
//             if (!isalpha(token[i]) && token[i] != '_')
//                 return false;
//         }
//         else
//         {
//             if (!isalnum(token[i]) && token[i] != '_')
//                 return false;
//         }
// 		i++;
//     }
//     return true;
// }

// static bool is_command(t_token *token)
// {
// 	if (!token || token->type != T_WORD)
// 		return (false);
// 	if (!token->prev)
// 		return (true);
// 	if(token->prev->type == T_PIPE)
// 		return (true);
// 	if (token->prev->type == T_REDIR_IN || token->prev->type == T_REDIR_OUT || token->prev->type == T_APPEND || token->prev->type == T_HEREDOC || (token->prev->type == T_WORD && token->prev->word_type == FILENAME))
// 		return (is_command(token->prev));
// 	return (false);
// }

// void tokenize_word(t_token *token)
// {
// 	while (token)
// 	{
// 		if (token->type == T_WORD)
// 		{
// 			if (is_filename(token->prev))
// 				token->word_type = FILENAME;
// 			else if (is_heredoc_delim(token->prev))
// 				token->word_type = HEREDOC_DELIM;
// 			else if (is_assignment(token->value))
// 				token->word_type = ASSIGNMENT;
// 			else if (is_builtin(token))
// 				token->word_type = BUILTIN;
// 			else if (is_command(token))
// 				token->word_type = COMMAND;
// 			else
// 				token->word_type = ARGUMENT;
// 		}
// 		token = token->next;
// 	}
// }
