/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalbano <dalbano@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 11:15:34 by dalbano           #+#    #+#             */
/*   Updated: 2025/07/08 13:29:02 by dalbano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"

// parsing
int		process_and_execute_input(t_shell *shell);

// lexer
t_token	*lexer(char *input);

// validate input
bool	valid_input(const char *input);

// handle input
void	handle_word(t_token **token, char *input, int *i);
void	handle_empty_quote(t_token **token, int *i);
void	handle_pipe(t_token **token, int *i);
void	handle_redirectory(t_token **token, char *input, int *i);

// create token
t_token	*new_token(t_token_type type, char *value);
t_token	*token_last(t_token *token);
void	token_add_back(t_token **token, t_token *new);

// utils
bool	is_token_seperator(char c);
int		calc_word_length(char *input, int i);
void	init_token(t_token *token);

// error
void	free_token(t_token *token);

// handle word
bool	is_builtin(t_token *token);

#endif /* PARSING_H */