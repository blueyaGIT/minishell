/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkloters <lkloters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/20 00:00:00 by lkloters          #+#    #+#             */
/*   Updated: 2026/07/20 00:00:00 by lkloters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token	*create_pipe_token(void)
{
	t_token	*pipe;

	pipe = malloc(sizeof(t_token));
	if (!pipe)
		return (NULL);
	pipe->value = ft_strdup("|");
	if (!pipe->value)
	{
		free(pipe);
		return (NULL);
	}
	pipe->type = T_PIPE;
	pipe->is_echo = 0;
	pipe->is_echo_n = 0;
	pipe->is_removed = 0;
	pipe->add_space = 0;
	pipe->next = NULL;
	pipe->prev = NULL;
	return (pipe);
}

static t_token	*create_cat_token(void)
{
	t_token	*cat;

	cat = malloc(sizeof(t_token));
	if (!cat)
		return (NULL);
	cat->value = ft_strdup("cat");
	if (!cat->value)
	{
		free(cat);
		return (NULL);
	}
	cat->type = 7;
	cat->is_echo = 0;
	cat->is_echo_n = 0;
	cat->is_removed = 0;
	cat->add_space = 0;
	cat->next = NULL;
	cat->prev = NULL;
	return (cat);
}

static int	link_cat_token(t_token *pipe, t_token *next_token)
{
	t_token	*cat;

	cat = create_cat_token();
	if (!cat)
		return (0);
	cat->prev = pipe;
	cat->next = next_token;
	pipe->next = cat;
	if (next_token)
		next_token->prev = cat;
	return (1);
}

static int	insert_pipe_at(t_token *current, int first_is_cat,
	t_token **out_next)
{
	t_token	*pipe;
	t_token	*next_token;

	pipe = create_pipe_token();
	if (!pipe)
		return (0);
	next_token = current->next->next;
	pipe->prev = current->next;
	pipe->next = next_token;
	current->next->next = pipe;
	if (next_token)
		next_token->prev = pipe;
	if (first_is_cat && !link_cat_token(pipe, next_token))
	{
		free(pipe);
		return (0);
	}
	*out_next = next_token;
	return (1);
}

int	insert_pipe(t_token *token)
{
	t_token	*current;
	t_token	*next_token;
	int		first_is_cat;

	current = token;
	first_is_cat = (token && token->type == 7 && token->value
			&& ft_strcmp(token->value, "cat") == 0);
	while (current && current->next && current->next->next)
	{
		if (current->type == T_HEREDOC && current->next->type == HEREDOC_DELIM
			&& current->next->next->type != T_PIPE)
		{
			if (!insert_pipe_at(current, first_is_cat, &next_token))
				return (0);
			current = next_token;
		}
		else
			current = current->next;
	}
	return (1);
}
