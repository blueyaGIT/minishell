/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_logo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalbano <dalbano@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 14:47:32 by dalbano           #+#    #+#             */
/*   Updated: 2025/09/08 14:47:33 by dalbano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_username(char **envp)
{
	char	*u;
	char	*slash;
	int		i;

	u = NULL;
	i = 0;
	while (envp[i])
	{
		if (ft_strstr(envp[i], "PWD=/Users/") == envp[i])
		{
			u = envp[i] + ft_strlen("PWD=/Users/");
			break ;
		}
		i++;
	}
	if (u != NULL)
	{
		slash = ft_strchr(u, '/');
		if (!slash)
			slash = u + ft_strlen(u);
		u = ft_strndup(u, ft_strlen(u) - ft_strlen(slash));
		ft_printf(BOLD LIGHT_PINK
			"\n🧚 " ITALIC " Hello, %s" RESET BOLD "  🧚\n\n" RESET, u);
		free(u);
	}
}

void	ft_print_logo(char **envp)
{
	ft_printf("\033[H\033[J");
	ft_printf("\n\n\n" MAGENTA "███████████████████████████████████████"
		"███████████████████████████████████████████████████\n\n" LIGHT_PINK
		"     ███████╗ █████╗ ██╗██████╗"
		" ██╗   ██╗    ███████╗██╗  ██╗███████╗██╗     ██╗     🧚 \n"
		"     ██╔════╝██╔══██╗██║██╔══██╗╚██╗ ██╔╝"
		"    ██╔════╝██║  ██║██╔════╝██║     ██║    O   \n"
		"     █████╗  ███████║██║██████╔╝ ╚████╔╝"
		"     ███████╗███████║█████╗  ██║     ██║   o    \n"
		"     ██╔══╝  ██╔══██║██║██╔══██╗  ╚██╔╝ "
		"     ╚════██║██╔══██║██╔══╝  ██║     ██║        \n"
		"     ██║     ██║  ██║██║██║  ██║   ██║  "
		"     ███████║██║  ██║███████╗███████╗███████╗   \n"
		"     ╚═╝     ╚═╝  ╚═╝╚═╝╚═╝  ╚═╝   ╚═╝  "
		"     ╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝   \n\n"
		"               ------------ Now with 100%%"
		" More Pixie Dust ------------           \n\n" MAGENTA
		"█████████████████████████████████████████"
		"█████████████████████████████████████████████████\n" LIGHT_PINK
		"\n"
		"                             	" LIGHT_PINK UNDERLINE ITALIC
		"lkloters" NO_UNDERLINE LIGHT_PINK " && " UNDERLINE "dalbano\n"
		"\033[0m"
		"\n");
	print_username(envp);
}
