/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_extractor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalbano <dalbano@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 15:50:36 by dalbano           #+#    #+#             */
/*   Updated: 2025/04/10 14:33:25 by dalbano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <ctype.h>

// Function to check if a token is a potential file path
int	is_filepath(const char *token)
{
	if (token[0] == '-' || strstr(token, "=") != NULL)
	{
		return (0);
	}
	if (strchr(token, '/') || strchr(token, '.'))
	{
		return (1);
	}
	return (0);
}

// Function to extract file paths from shell input
void	extract_filepaths(const char *input)
{
	char	*input_copy;
	char	*token;
	int		first;

	input_copy = ft_strdup((char *)input);
	if (!input_copy)
	{
		perror("ft_strdup");
		return ;
	}
	token = strtok(input_copy, " ");
	first = 1;
	while (token)
	{
		if (!first && is_filepath(token))
		{
			printf("Found file path: %s\n", token);
		}
		first = 0;
		token = strtok(NULL, " ");
	}
	free(input_copy);
}
