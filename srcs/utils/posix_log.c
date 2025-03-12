/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   posix_log.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalbano <dalbano@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:08:45 by dalbano           #+#    #+#             */
/*   Updated: 2025/03/12 16:08:54 by dalbano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int write_log(const char *message) {
    int fd = open(LOG_PATH, O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (fd == -1) {
        return -1;
    }
    time_t now;
    time(&now);
    struct tm *timeinfo = localtime(&now);
    char timestamp[32];
    strftime(timestamp, sizeof(timestamp), "[%Y-%m-%d %H:%M:%S] ", timeinfo);
    char buffer[BUFFER_SIZE];
    int len = snprintf(buffer, BUFFER_SIZE, "%s%s\n", timestamp, message);
    if (len < 0 || len >= BUFFER_SIZE) {
        close(fd);
        return -1;
    }
    ssize_t bytes_written = write(fd, buffer, len);
    int close_result = close(fd);
    return (bytes_written == len && close_result == 0) ? 0 : -1;
}
