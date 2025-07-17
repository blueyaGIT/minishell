

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
		printf(BOLD LIGHT_PINK
			"\n🧚 " ITALIC " Hello, %s" RESET BOLD "  🧚\n\n" RESET, u);
		free(u);
	}
}

void	ft_print_logo(char **envp)
{
	printf("\033[H\033[J");
	printf("\n\n\n" MAGENTA "███████████████████████████████████████"
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
