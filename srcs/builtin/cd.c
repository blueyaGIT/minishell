/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalbano <dalbano@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 15:05:33 by dalbano           #+#    #+#             */
/*   Updated: 2025/04/12 14:38:24 by dalbano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_cd(t_shell *shell, char **args)
{
	(void) shell;
	printf("%s\n%s\n", args[0], args[1]);
	return (0);
	// check if any args
	// save cwd as pwd
	// check if target exists
	// -> if success then save pwd as ENV->OLDPWD
}
