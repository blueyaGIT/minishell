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
	char	*template;
	int		fd;

	template = ft_strdup("/tmp/minishell_heredoc_XXXXXX");
	if (!template)
		return (NULL);
	fd = mkstemp(template);
	if (fd == -1)
	{
		free(template);
		return (NULL);
	}
	close(fd);
	return (template);
}

int	open_heredoc_temp(char *temp_file)
{
	int	temp_fd;

	temp_fd = open(temp_file, O_WRONLY | O_TRUNC);
	if (temp_fd == -1)
	{
		perror("heredoc temp file");
		return (-1);
	}
	return (temp_fd);
}
