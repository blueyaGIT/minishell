/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalbano <dalbano@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 11:15:34 by dalbano           #+#    #+#             */
/*   Updated: 2025/07/04 14:54:58 by dalbano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"

t_token	*new_token(t_token_type type, char *value);
t_token	*token_last(t_token *token);
void	token_add_back(t_token **token, t_token *new);
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
#endif /* PARSING_H */