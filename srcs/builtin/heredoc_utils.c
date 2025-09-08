/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalbano <dalbano@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 14:44:43 by dalbano           #+#    #+#             */
/*   Updated: 2025/09/08 14:44:44 by dalbano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*generate_temp_filename(void)
{
	static int	counter = 0;
	char		*filename;
	char		*counter_str;

	counter_str = ft_itoa(counter++);
	if (!counter_str)
		return (NULL);
	filename = ft_strjoin("/tmp/heredoc_temp_", counter_str);
	free(counter_str);
	return (filename);
}

int	open_heredoc_temp(char *temp_file)
{
	int	temp_fd;

	temp_fd = open(temp_file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (temp_fd == -1)
	{
		perror("heredoc temp file");
		return (-1);
	}
	return (temp_fd);
}
