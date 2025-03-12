#include "../../includes/minishell.h"

int syntax_error(const char *str)
{
	int i = 0;
	int piped_already = 0;
	int found_word = 0;

	while(str[i] != '\0')
	{
		if(str[i] == '|')
		{
			if(str[i + 1] == '|')
			{
				printf("Syntaxerror: '||' found! \n");
				return(1);
			}
			if(piped_already || !found_word)
			{
				printf("Syntaxerror: '|' stands alone \n");
				return(1);
			}
			piped_already = 1;
		}
		else if(str[i] != ' ')
		{
			found_word = 1;
			piped_already = 0;
		}
		i++;
	}
	return(0);
}