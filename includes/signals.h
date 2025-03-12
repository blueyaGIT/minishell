#ifndef SIGNALS_H
# define SIGNALS_H

# include "minishell.h"

void	init_signals(void);
void	switch_to_normal_mode(void);
void	sigint_handler_normal(int signbr);
void	switch_to_heredoc_mode(void);
void	sigint_handler_heredoc(int signbr);

#endif /* SIGNALS_H */