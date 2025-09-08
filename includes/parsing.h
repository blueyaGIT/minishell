/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalbano <dalbano@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 14:42:56 by dalbano           #+#    #+#             */
/*   Updated: 2025/09/08 14:42:58 by dalbano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"

int			process_and_execute_input(t_shell *shell);
t_command	*parse_code(t_token *token);
bool		valid_syntax(t_token *token);
t_token		*handle_word(t_token *token, t_command **command);
t_token		*handle_pipe(t_token *token, t_command **command);
t_token		*handle_redirection(t_token *token, t_command **command);
void		command_add_back(t_command **command, t_command *new);
t_command	*command_last(t_command *command);
t_command	*new_command(void);
void		init_command(t_command *command);
bool		is_word(t_token_type type);
bool		is_redirection_token(t_token *token);

#endif /* PARSING_H */