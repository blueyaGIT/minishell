/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalbano <dalbano@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 15:51:54 by dalbano           #+#    #+#             */
/*   Updated: 2025/04/12 15:53:06 by dalbano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Helper function that concatenates three strings.
Assumes ft_strjoin exists.
*/
char	*ft_strjoin_three(const char *s1, const char *s2, const char *s3)
{
    char	*tmp;
    char	*result;

    tmp = ft_strjoin(s1, s2);
    result = ft_strjoin(tmp, s3);
    free(tmp);
    return (result);
}
