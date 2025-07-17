

#ifndef FORMAT_H
# define FORMAT_H

# include "minishell.h"

/* Text formatting */
# define RESET		"\033[0m"
# define BOLD		"\033[1m"
# define DIM		"\033[2m"
# define ITALIC		"\033[3m"
# define UNDERLINE	"\033[4m"
# define CLEARLINE	"\033[2K"
# define MOVEUP		"\033[A"

/* Standard Colours */
# define BLACK		"\033[30m"
# define RED		"\033[31m"
# define GREEN		"\033[32m"
# define YELLOW		"\033[33m"
# define BLUE		"\033[34m"
# define MAGENTA	"\033[35m"
# define CYAN		"\033[36m"
# define LIGHT_PINK "\033[38;5;168m"
# define WHITE		"\033[37m"

/* Extended: Background Colours */
# define BG_BLACK	"\033[40m"
# define BG_RED		"\033[41m"
# define BG_GREEN	"\033[42m"
# define BG_YELLOW	"\033[43m"
# define BG_BLUE	"\033[44m"
# define BG_MAGENTA	"\033[45m"
# define BG_CYAN	"\033[46m"
# define BG_WHITE	"\033[47m"

/* Extended: Bright Colours */
# define BRIGHT_BLACK	"\033[90m"
# define BRIGHT_RED		"\033[91m"
# define BRIGHT_GREEN	"\033[92m"
# define BRIGHT_YELLOW	"\033[93m"
# define BRIGHT_BLUE	"\033[94m"
# define BRIGHT_MAGENTA	"\033[95m"
# define BRIGHT_CYAN	"\033[96m"
# define BRIGHT_WHITE	"\033[97m"

/* Extended: Additional Text Effects */
# define BLINK       	  "\033[5m"
# define REVERSE     	  "\033[7m"
# define HIDDEN      	  "\033[8m"
# define STRIKETHROUGH    "\033[9m"
# define OVERLINED        "\033[53m"  // Also known as "double overline"
# define FRAMED           "\033[51m"  // Add a frame around the text
# define ENCIRCLED        "\033[52m"  // Encircle the text

/* Extended: Reset Specific Text Effects */
# define NO_BOLD          "\033[22m"  // Normal intensity (cancel bold)
# define NO_ITALIC        "\033[23m"  // Cancel italic
# define NO_UNDERLINE     "\033[24m"  // Cancel underline
# define NO_BLINK         "\033[25m"  // Cancel blink
# define NO_REVERSE       "\033[27m"  // Cancel reverse
# define NO_HIDDEN        "\033[28m"  // Cancel hidden
# define NO_STRIKETHROUGH "\033[29m"  // Cancel strikethrough

#endif /* FORMAT_H */
