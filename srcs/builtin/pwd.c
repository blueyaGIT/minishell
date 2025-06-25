/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalbano <dalbano@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 15:09:03 by dalbano           #+#    #+#             */
/*   Updated: 2025/04/12 14:31:00 by dalbano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_pwd(t_shell *shell)
{
	char	buf[PATH_MAX];
	char	*cwd;

	cwd = getcwd(buf, PATH_MAX);
	if (cwd)
	{
		ft_fprintf(STDOUT_FILENO, "%s\n", cwd);
		return (EXIT_SUCCESS);
	}
	print_error("PWD", shell);
	return (EXIT_FAILURE);
}
