/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalbano <dalbano@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 14:42:17 by dalbano           #+#    #+#             */
/*   Updated: 2025/09/08 14:42:19 by dalbano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# include "minishell.h"

int		syntax_error(const char *str, t_shell *shell);
int		check_unclosed_quotes(const char *input, t_shell *shell);
void	set_exit_code(t_shell *shell, int error_type);
int		run_syntax_checks(t_shell *shell);
int		check_empty_input(const char *str, t_shell *shell);
int		check_redirect_syntax(const char *str, t_shell *shell);
int		check_redirections(t_command *cmd, t_shell *shell);
int		print_error(const char *message, t_shell *shell);
#endif /* ERROR_H */