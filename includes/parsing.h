/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalbano <dalbano@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 11:15:34 by dalbano           #+#    #+#             */
/*   Updated: 2025/07/02 14:16:50 by dalbano          ###   ########.fr       */
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
#endif /* PARSING_H */