/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_logo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalbano <dalbano@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 15:20:37 by dalbano           #+#    #+#             */
/*   Updated: 2025/03/24 15:01:42 by dalbano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_username(char **envp)
{
	char	*username;
	int		i;

	username = NULL;
	i = 0;
	while (envp[i])
	{
        if (ft_strstr(envp[i], "USER=") == envp[i])
		{
			username = envp[i] + ft_strlen("USER=");
            break;
        }
        i++;
    }
	if (username)
		printf(BOLD LIGHT_PINK"\n🧚 " ITALIC " Hello, %s" RESET BOLD "  🧚\n\n"RESET, username);
}

void	ft_print_logo(char **envp)
{
	printf("\033[H\033[J");
	printf(
		"\n\n\n"
		MAGENTA
		"██████████████████████████████████████████████████████████████████████████████████████████\n\n"
		LIGHT_PINK
		"	███████╗ █████╗ ██╗██████╗ ██╗   ██╗███████╗██╗  ██╗███████╗██╗     ██╗     🧚 \n"
		"	██╔════╝██╔══██╗██║██╔══██╗╚██╗ ██╔╝██╔════╝██║  ██║██╔════╝██║     ██║    O   \n"
		"	█████╗  ███████║██║██████╔╝ ╚████╔╝ ███████╗███████║█████╗  ██║     ██║   o    \n"
		"	██╔══╝  ██╔══██║██║██╔══██╗  ╚██╔╝  ╚════██║██╔══██║██╔══╝  ██║     ██║        \n"
		"	██║     ██║  ██║██║██║  ██║   ██║   ███████║██║  ██║███████╗███████╗███████╗   \n"
		"	╚═╝     ╚═╝  ╚═╝╚═╝╚═╝  ╚═╝   ╚═╝   ╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝   \n"
		"\n"
		"		------------ Now with 100%% More Pixie Dust ------------           \n"
		"\n"
		MAGENTA
		"██████████████████████████████████████████████████████████████████████████████████████████\n"
		LIGHT_PINK
		"\n"
		"				"
		LIGHT_PINK UNDERLINE ITALIC
		"lnierobi" NO_UNDERLINE LIGHT_PINK" && " UNDERLINE"dalbano\n"
		"\033[0m" // Reset color
		"\n");
	print_username(envp);
}
