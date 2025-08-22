


valgrind --leak-check=full --show-leak-kinds=all --suppressions=/app/core/minishell/srcs/supp.supp --track-origins=yes ./minishell

valgrind --leak-check=full --show-leak-kinds=all --suppressions=/app/core/minishell/srcs/readline.supp --track-origins=yes --verbose ./minishell 


TODO

- [x] Heredoc ohne command
- [x] Heredoc als builtin splitten
- [x] check if env variable already exists
	- if yes -> replace value
- [x] Echo segfaults
- [x] env mit quotes
- [x] echo space arg
- [x] env-var initialization als ein char ("Test=test")