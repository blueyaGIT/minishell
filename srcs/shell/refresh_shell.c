/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refresh_shell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalbano <dalbano@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 18:35:50 by dalbano           #+#    #+#             */
/*   Updated: 2025/04/03 09:36:59 by dalbano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_delone_token(t_token *lst, void (*del)(void *))
{
    if (!lst)
        return ;
    if (del && lst->token_value)
    {
        del(lst->token_value);
        lst->token_value = NULL;
    }
    del(lst);
}

void	ft_free_token(t_token **lst, void (*del)(void *))
{
	t_token	*temp;

	temp = NULL;
	while (*lst != NULL)
	{
		temp = (*lst)->next;
		ft_delone_token(*lst, del);
		*lst = temp;
	}
}

static void	ft_delone_node(t_node *node, void (*del)(void *))
{
	if (node->args)
        (*del)(node->args);
    if (node->filename)
        ft_free_arr(node->filename);
    if (node->redirections)
        ft_free_arr(node->redirections);
    (*del)(node);
}

void	ft_free_node(t_node **lst, void (*del)(void *))
{
	t_node	*temp;

	temp = NULL;
	while (*lst != NULL)
	{
		temp = (*lst)->next;
		ft_delone_node(*lst, del);
		*lst = temp;
	}
}

void	refresh_shell(t_shell *shell)
{
	if (!shell)
		return ;
	if (shell->input)
		ft_free_ptr(shell->input);
	// if (shell->token_ll)
	// 	ft_free_token(&shell->token_ll, &ft_free_ptr);
}
