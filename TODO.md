


valgrind --leak-check=full --show-leak-kinds=all --suppressions=/app/core/minishell/srcs/supp.supp --track-origins=yes ./minishell

valgrind --leak-check=full --show-leak-kinds=all --suppressions=/app/core/minishell/srcs/readline.supp --track-origins=yes --verbose ./minishell 


TODO

- [ ] Heredoc ohne command
- [ ] Heredoc als builtin splitten
- [ ] Echo segfaults
- [ ] env mit quotes
- [ ] echo space arg
- [ ] env-var initialization als ein char ("Test=test")