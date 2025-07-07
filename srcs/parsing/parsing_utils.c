/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkloters <lkloters@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 16:22:36 by lkloters          #+#    #+#             */
/*   Updated: 2025/07/07 16:27:16 by lkloters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int count_arguments(t_token *token)
{
	int count;
	count = 0;
	while (token && token->type == T_WORD)
	{
		count++;
		token = token->next;
	}
	return (count);
}