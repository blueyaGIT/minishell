#ifndef ERROR_H
# define ERROR_H

# include "minishell.h"

int	syntax_error(const char *str);
int	check_unclosed_quotes(const char *input);

#endif /* ERROR_H */