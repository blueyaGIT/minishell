/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkloters <lkloters@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 11:15:34 by dalbano           #+#    #+#             */
/*   Updated: 2025/07/09 10:44:57 by lkloters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"

//lexer
t_token *lexer(char *input);
bool valid_input(const char *input);

// lexer utils
void	init_token(t_token *token);
bool is_token_seperator(char c);
int calc_word_length(char *input, int i);

// create token
void	token_add_back(t_token **token, t_token *new);
t_token	*token_last(t_token *token);
t_token *new_token(t_token_type type, char *value);

// handle input
void handle_redirectory(t_token **token, char *input, int *i);
void handle_pipe(t_token **token, int *i);
void handle_empty_quote(t_token **token, int *i);
void handle_word(t_token **token, char *input, int *i);

// tokenize words
// void tokenize_word(t_token *token);
// bool is_builtin(t_token *token);

// create token
// t_token *new_token(t_token_type type, char *value);
// t_token	*token_last(t_token *token);
// void	token_add_back(t_token **token, t_token *new);

// parsing
int process_and_execute_input(t_shell *shell);
// t_command *parse_code(t_token *token);
// bool valid_syntax(t_token *token);


#endif /* PARSING_H */