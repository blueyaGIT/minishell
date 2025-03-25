/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalbano <dalbano@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 16:56:30 by dalbano           #+#    #+#             */
/*   Updated: 2025/03/25 15:33:38 by dalbano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static void	rm_line(char *line)
// {
// 	size_t	len;
	
// 	if (!line)
// 		return ;
// 	len = ft_strlen(line);
// 	if (len > 0 && line[len - 1] == '\n')
// 		line[len - 1] = '\0';
// }

// void	history_init(void)
// {
// 	int	fd;
// 	char	*line;

	
// 	fd = open(get_shell()->history_file, O_RDONLY | O_CREAT, 0644);
// 	if (fd < 0)
// 	{
// 		ft_fprintf(STDERR_FILENO, RED "Error: History file not accessible\n" RESET);
// 		return ;
// 	}
// 	line = get_next_line(fd);
// 	while (line)
// 	{
// 		rm_line(line);
// 		add_history(line);
// 		free(line);
// 		line = get_next_line(fd);
// 	}
// 	close(fd);
// }