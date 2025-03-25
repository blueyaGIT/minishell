#include "minishell.h"

// int syntax_error(const char *str)
// {
// 	int i = 0;
// 	int piped_already = 0;
// 	int found_word = 0;

// 	while(str[i] != '\0')
// 	{
// 		if(str[i] == '|')
// 		{
// 			if(str[i + 1] == '|')
// 			{
// 				printf("Syntaxerror: '||' found! \n");
// 				return(1);
// 			}
// 			if(piped_already || !found_word)
// 			{
// 				printf("Syntaxerror: '|' stands alone \n");
// 				return(1);
// 			}
// 			piped_already = 1;
// 		}
// 		else if(str[i] != ' ')
// 		{
// 			found_word = 1;
// 			piped_already = 0;
// 		}
// 		i++;
// 	}
// 	return(0);
// }

int syntax_error(const char *str, t_shell *shell)
{
    int i = 0;
    int piped_already = 0;
    int found_word = 0;

    while (str[i] != '\0')
    {
        if (str[i] == '|')
        {
            if (str[i + 1] == '|')
            {
                printf("Syntaxerror: '||' found! \n");
                set_exit_code(shell, 1); // Fehlercode 1 für Syntaxfehler
                return 1;
            }
            if (piped_already || !found_word)
            {
                printf("Syntaxerror: '|' stands alone \n");
                set_exit_code(shell, 1); // Fehlercode 1 für Syntaxfehler
                return 1;
            }
            piped_already = 1;
        }
        else if (str[i] != ' ')
        {
            found_word = 1;
            piped_already = 0;
        }
        i++;
    }

    set_exit_code(shell, 0); // Keine Fehler
    return 0;
}


// int check_unclosed_quotes(const char *input)
// {
//     int single_quotes = 0;
//     int double_quotes = 0;

//     while (*input)
//     {
//         if (*input == '\'')
//             single_quotes = !single_quotes; 
//         else if (*input == '"')
//             double_quotes = !double_quotes; 
//         input++;
//     }

//     if (single_quotes || double_quotes)
//     {
//         printf("Syntax Error: Unclosed quotes detected.\n");
//         return 1; 
//     }
//     return 0;
// }

int check_unclosed_quotes(const char *input, t_shell *shell)
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
        set_exit_code(shell, 2); // Fehlercode 2 für ungeschlossene Anführungszeichen
        return 1; 
    }

    set_exit_code(shell, 0); // Keine Fehler
    return 0;
}

void set_exit_code(t_shell *shell, int error_type)
{
    if (error_type == 0) {
        // Keine Fehler, Exit-Code auf 0 setzen
        shell->lastexitcode = 0;
    } 
    else if (error_type == 1) {
        // Fehler bei der Syntax, Exit-Code auf 2 setzen (Syntax-Fehler)
        shell->lastexitcode = 2;
    } 
    else if (error_type == 2) {
        // Unclosed quotes, Exit-Code auf 1 setzen
        shell->lastexitcode = 1;
    }
    printf("Exit-Code gesetzt: %d\n", shell->lastexitcode);  // Debugging-Ausgabe
	printf("$? : %d\n", shell->lastexitcode);  // Ausgabe des Exit-Codes

}

