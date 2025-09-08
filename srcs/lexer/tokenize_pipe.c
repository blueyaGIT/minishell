/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalbano <dalbano@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 14:46:42 by dalbano           #+#    #+#             */
/*   Updated: 2025/09/08 14:46:43 by dalbano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	tokenize_pipe(t_token **token, int *i)
{
	token_add_back(token, new_token(T_PIPE, ft_strdup("|")));
	(*i)++;
}
