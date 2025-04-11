/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_extractor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalbano <dalbano@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 15:50:36 by dalbano           #+#    #+#             */
/*   Updated: 2025/04/11 15:24:20 by dalbano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <ctype.h>

// Function to check if a tk is a potential file path
int	is_filepath(const char *tk)
{
	if (tk[0] == '-' || strstr(tk, "=") != NULL)
	{
		return (0);
	}
	if (strchr(tk, '/') || strchr(tk, '.'))
	{
		return (1);
	}
	return (0);
}

// Function to extract file paths from shell input
void	extract_filepaths(const char *input)
{
	char	*input_copy;
	char	*tk;
	int		first;

	input_copy = ft_strdup((char *)input);
	if (!input_copy)
	{
		perror("ft_strdup");
		return ;
	}
	tk = strtok(input_copy, " ");
	first = 1;
	while (tk)
	{
		if (!first && is_filepath(tk))
		{
			printf("Found file path: %s\n", tk);
		}
		first = 0;
		tk = strtok(NULL, " ");
	}
	free(input_copy);
}
