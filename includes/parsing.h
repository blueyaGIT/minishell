/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkloters <lkloters@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 11:15:34 by dalbano           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/07/05 14:05:06 by lkloters         ###   ########.fr       */
=======
/*   Updated: 2025/07/04 14:54:58 by dalbano          ###   ########.fr       */
>>>>>>> 4aae29301e4a46862f1da7dbbe1a2ce1f86e7892
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"

//parsing
int process_and_execute_input(t_shell *shell);

// lexer
t_token *lexer(char *input);

// validate input
bool valid_input(const char *input);

// handle input
void handle_word(t_token **token, char *input, int *i);
void handle_empty_quote(t_token **token, int *i);
void handle_pipe(t_token **token, int *i);
void handle_redirectory(t_token **token, char *input, int *i);

// create token
t_token *new_token(t_token_type type, char *value);
t_token	*token_last(t_token *token);
void	token_add_back(t_token **token, t_token *new);
<<<<<<< HEAD

//utils
bool is_token_seperator(char c);
int calc_word_length(char *input, int i);
void	init_token(t_token *token);

//error
void	free_token(t_token *token);

// handle word
void handle_word(t_token *token);
bool is_builtin(t_token *token);

=======
void	handle_redirectory(t_token **token, char *input, int *i);
bool	is_redirectory(char c);
t_token	*lexer(char *input);
int		calc_word_length(char *input, int i);
bool	is_token_seperator(char c);
bool	is_empty_quote(char *input, int i);
bool	after_is_word(char *input, int i);
bool	before_is_word(char *input, int i);
void	handle_pipe(t_token **token, int *i);
void	handle_empty_quote(t_token **token, int *i);
int		parse_word_content(char *input, int *i, char *word, int length);
void	handle_word(t_token **token, char *input, int *i);
bool	valid_input(const char *input);
>>>>>>> 4aae29301e4a46862f1da7dbbe1a2ce1f86e7892
#endif /* PARSING_H */