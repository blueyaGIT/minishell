/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkloters <lkloters@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 16:22:36 by lkloters          #+#    #+#             */
/*   Updated: 2025/07/14 17:01:40 by lkloters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void init_command(t_command *command)
{
	if (!command)
		return ;
	command->args = NULL;
	command->next = NULL;
	command->prev = NULL;
}

bool is_word(t_token_type type)
{
	if (type == BUILTIN || type == COMMAND || type == ARGUMENT || type == ASSIGNMENT || type == FILENAME || type == HEREDOC_DELIM)
		return (true);
	return (false);
}