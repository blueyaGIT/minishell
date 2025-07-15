/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkloters <lkloters@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 11:15:34 by dalbano           #+#    #+#             */
/*   Updated: 2025/07/15 14:22:51 by lkloters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"

//lexer
t_token *lexer(char *input, t_shell *shell);
bool valid_input(const char *input);

// lexer utils
void	init_token(t_token *token);
bool is_token_seperator(char c);
int calc_word_length(char *input, int i);

// // create token
void	token_add_back(t_token **token, t_token *new);
t_token	*token_last(t_token *token);
t_token *new_token(t_token_type type, char *value);

// // handle input
void tokenize_redirection(t_token **token, char *input, int *i);
void tokenize_pipe(t_token **token, int *i);
void handle_empty_quote(t_token **token, int *i);
void tokenize_word(t_token **token, char *input, int *i);

// handle env
char *handle_env(t_shell *shell);
char *handle_tilde_expansion(char *input_dup, int start, int *i, t_shell *shell);
char *handle_dollar_expansion(char *input_dup, int start, int *i, t_shell *shell);

// tokenize words
void tokenize_word_token(t_token *token);
bool is_builtin(t_token *token);

// create token
t_token *new_token(t_token_type type, char *value);
t_token	*token_last(t_token *token);
void	token_add_back(t_token **token, t_token *new);

// parsing
int process_and_execute_input(t_shell *shell);
t_command *parse_code(t_token *token);
bool valid_syntax(t_token *token);
t_token *handle_word(t_token *token, t_command **command);
t_token *handle_pipe(t_token *token, t_command **command);
t_token *handle_redirection(t_token *token, t_command **command);


// create command
void	command_add_back(t_command **command, t_command *new);
t_command	*command_last(t_command *command);
t_command *new_command(void);

// parsing utils
void init_command(t_command *command);
bool is_word(t_token_type type);
bool is_redirection_token(t_token *token);
void init_redir(t_redir *redir);


#endif /* PARSING_H */