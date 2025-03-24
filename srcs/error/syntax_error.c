#include "minishell.h"

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

int check_unclosed_quotes(const char *input)
{
    int single_quotes = 0;
    int double_quotes = 0;

    while (*input)
    {
        if (*input == '\'')
            single_quotes = !single_quotes; 
        else if (*input == '"')
            double_quotes = !double_quotes; 
        input++;
    }

    if (single_quotes || double_quotes)
    {
        printf("Syntax Error: Unclosed quotes detected.\n");
        return 1; 
    }
    return 0;
}
