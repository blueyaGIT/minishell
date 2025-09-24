


valgrind --leak-check=full --show-leak-kinds=all --suppressions=/home/lkloters/42/projects/circle3/minishell/srcs/readline.supp --track-origins=yes --verbose ./minishell
valgrind --leak-check=full --show-leak-kinds=all --suppressions=./srcs/utils/readline.supp --track-origins=yes --track-fds=yes ./minishell
valgrind --leak-check=full --show-leak-kinds=all --suppressions=./sub.sub --track-origins=yes --track-fds=yes ./minishell


TODO

# LILLI
- [x] $?
- [x] echo error msg

# MARZIA
- [x] exit 42
- [x] free proof everything
- [x] signals


- [ ][fix export && weg](./srcs/builtin/export_utils.c#L56)
- [ ][\n in error msgs](./srcs/exection/bin.c#L45)
- [ ][itterate through cmd_list when creating files](./srcs/io/fix_redir.c)
