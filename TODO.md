

- [ ][check "init_value(new)" error: function not found](./srcs/lexer/create_token.c#L22)

valgrind --leak-check=full --show-leak-kinds=all --suppressions=/app/core/minishell/srcs/supp.supp --track-origins=yes ./minishell

valgrind --leak-check=full --show-leak-kinds=all --suppressions=/app/core/minishell/srcs/readline.supp --track-origins=yes --verbose ./minishell 

LEAKS
- [ ][handle_pipe](./srcs/parsing/create_command.c#L7)
- [ ][handle_env](./srcs/lexer/handle_env.c#L60)
- [ ][handle_word](./srcs/parsing/parse_tokens.c#L25)
- [ ][handle_word](./srcs/parsing/parse_tokens.c#L55)