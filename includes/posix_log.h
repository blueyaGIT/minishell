#ifndef POSIX_LOG_H
#define POSIX_LOG_H
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <sys/stat.h>
#define LOG_PATH "./minishell.log"
#define BUFFER_SIZE 4096
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
#endif // POSIX_LOG_H