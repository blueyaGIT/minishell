/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refresh_shell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalbano <dalbano@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 18:35:50 by dalbano           #+#    #+#             */
/*   Updated: 2025/06/25 15:12:26 by dalbano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static void	ft_delone_token(t_token *lst, void (*del)(void *))
// {
// 	if (!lst)
// 		return ;
// 	if (del && lst->token_value)
// 	{
// 		del(lst->token_value);
// 		lst->token_value = NULL;
// 	}
// 	del(lst);
// }

// void	ft_free_token(t_token **lst, void (*del)(void *))
// {
// 	t_token	*temp;

// 	temp = NULL;
// 	while (*lst != NULL)
// 	{
// 		temp = (*lst)->next;
// 		ft_delone_token(*lst, del);
// 		*lst = temp;
// 	}
// }

// static void	ft_delone_node(t_node *node, void (*del)(void *))
// {
// 	if (node->args)
// 		(*del)(node->args);
// 	if (node->filename)
// 		ft_free_arr(node->filename);
// 	if (node->rds)
// 		ft_free_arr(node->rds);
// 	(*del)(node);
// }

// void	ft_free_node(t_node **lst, void (*del)(void *))
// {
// 	t_node	*temp;

// 	temp = NULL;
// 	while (*lst != NULL)
// 	{
// 		temp = (*lst)->next;
// 		ft_delone_node(*lst, del);
// 		*lst = temp;
// 	}
// }

void	refresh_shell(t_shell *shell)
{
	if (!shell)
		return ;
	ft_free_shell(shell);
}
